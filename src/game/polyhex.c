#include "polyhex.h"


static void _poly_invert(struct Polyhex poly) {
	for (int i = 0; i < poly.order; i++) {
		poly.hex[i].q = -poly.hex[i].q - poly.hex[i].r;
	}
}

static void _poly_rotate(struct Polyhex poly, int8_t rotation) {
	switch (rotation % 6) {
	case 1:
		for (int i = 0; i < poly.order; i++) {
			int16_t tmp_q = poly.hex[i].q;
			poly.hex[i].q = -poly.hex[i].r;
			poly.hex[i].r = tmp_q + poly.hex[i].r;
		}
		break;
	case 2:
		for (int i = 0; i < poly.order; i++) {
			int16_t tmp_q = poly.hex[i].q;
			poly.hex[i].q = -tmp_q - poly.hex[i].r;
			poly.hex[i].r = tmp_q;
		}
		break;
	case 3:
		for (int i = 0; i < poly.order; i++) {
			poly.hex[i].q = -poly.hex[i].q;
			poly.hex[i].r = -poly.hex[i].r;
		}
		break;
	case 4:
		for (int i = 0; i < poly.order; i++) {
			int16_t tmp_q = poly.hex[i].q;
			poly.hex[i].q = poly.hex[i].r;
			poly.hex[i].r = -tmp_q - poly.hex[i].r;
		}
		break;
	case 5:
		for (int i = 0; i < poly.order; i++) {
			int16_t tmp_q = poly.hex[i].q;
			poly.hex[i].q = tmp_q + poly.hex[i].r;
			poly.hex[i].r = -tmp_q;
		}
		break;
	default:
		break;
	}
}

bool poly_load(struct Polyhex* poly, FILE* file, int16_t q, int16_t r) {

	if (file != NULL) {
		rewind(file);
		char buffer[100];
		fscanf(file, "%100[^!]", buffer);
		fscanf(file, "!%100[^!]", buffer);
		int count = strtol(buffer, NULL, 10);
		int line = rand()%count;
		
		

		for (int i = 0; i < line; i++) {
			fscanf(file, "!%100[^!]", buffer);
		}
		fscanf(file, "%100[^!]", buffer);
		fscanf(file, "!%100[^/]", buffer);
		int order = strtol(buffer, NULL, 10);

		poly->order = order;
		poly->hex = (struct AVect*) calloc(order, sizeof(struct AVect));
		if (poly->hex == NULL) {
			fprintf(stderr, "ERROR WHILE LOADING THE POLYHEX");
		}

		fscanf(file, "/%100[^!]", buffer);
		char* token = strtok(buffer, "/");

		int i = 0;
		while (token != NULL && i < order) {
			int q, r;
			sscanf(token, "%d,%d", &q, &r);
			poly->hex[i].q = q;
			poly->hex[i].r = r;
			token = strtok(NULL, "/");
			i++;
		}

		poly->col = rand()%COLOR_TOTAL;
	  _poly_rotate(*poly, rand()%6);
		if (rand()%2 == 0) {
			_poly_invert(*poly);
		}
		poly->pos = (struct AVect) {q, r};
		poly->order = 4;

		return true;
	} else {
		return false;
	}

}



bool poly_move(struct Polyhex* poly, struct HexMap map, int16_t dq, int16_t dr) {
	poly->pos.q += dq;
	poly->pos.r += dr;
	if (is_colliding(map, *poly)) {
		poly->pos.q -= dq;
		poly->pos.r -= dr;
		return false;
	} else {
		return true;
	}
}



void poly_rotate_cw(struct Polyhex* poly, struct HexMap map) {
	struct AVect* backup = (struct AVect*) malloc(poly->order * sizeof(struct AVect));
	for (int i = 0; i < poly->order; i++) {
		backup[i] = poly->hex[i];
	}
	_poly_rotate(*poly, 1);
	if (is_colliding(map, *poly)) {
		free(poly->hex);
		poly->hex = backup;
	} else {
		free(backup);
	}
}

void poly_rotate_ccw(struct Polyhex* poly, struct HexMap map) {
	struct AVect* backup = (struct AVect*) malloc(poly->order * sizeof(struct AVect));
	for (int i = 0; i < poly->order; i++) {
		backup[i] = poly->hex[i];
	}
	_poly_rotate(*poly, -1);
	if (is_colliding(map, *poly)) {
		free(poly->hex);
		poly->hex = backup;
	} else {
		free(backup);
	}
}

void poly_move_up(struct Polyhex* poly_l, struct Polyhex* poly_r, struct HexMap map) {
	if (poly_move(poly_l, map, 0, -1)) {
		poly_move(poly_r, map, 1, -1);
	}
}

void poly_move_down(struct Polyhex* poly_l, struct Polyhex* poly_r, struct HexMap map) {
	if (poly_move(poly_l, map, -1 ,1)) {
		poly_move(poly_r, map, 0, 1);
	}
}