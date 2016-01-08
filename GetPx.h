/**
 * GetPx.h
 * Get the coordinate of any point on the screen.
 * @author Haruue Icymoon <Haruue Icymoon>
 * @version v1.0.1
 * @link https://github.com/haruue/GetPx_Ndless
 * @licence WTFPL
 */

#include <libndls.h>

void _reverse_pixel_(int x, int y) {
    volatile unsigned char *ptr;
    if (has_colors) {
        ptr = (volatile unsigned char *) SCREEN_BASE_ADDRESS;
        ptr += y * SCREEN_WIDTH * sizeof(short) + x * sizeof(short);
    } else {
        ptr = (volatile unsigned char *) SCREEN_BASE_ADDRESS + (x >> 1) + (y << 7) + (y << 5);
    }
    *(volatile unsigned short *) ptr =  ~(*(volatile unsigned short *) ptr);
}

void get_px() {
    int x=0, y=0;
    _reverse_pixel_(0, 0);

    while (!isKeyPressed(KEY_NSPIRE_ESC)) {
        /* Arrow key */
        /*    1
            2   3
              4    */
        int change = 0;
        if (isKeyPressed(KEY_NSPIRE_UP))
            change = 1;
        else if (isKeyPressed(KEY_NSPIRE_LEFT))
            change = 2;
        else if (isKeyPressed(KEY_NSPIRE_RIGHT))
            change = 3;
        else if (isKeyPressed(KEY_NSPIRE_DOWN))
            change = 4;
        else if (isKeyPressed(KEY_NSPIRE_ENTER)) {
            /* Show Coordinate */
            char *coordinate = (char *) malloc(sizeof(char) * 8);
            memset(coordinate, 0, sizeof(char) * 8);
            char *tmp = (char *) malloc(sizeof(char) * 3);
            itoa(x, tmp, 10);
            strcat(coordinate, tmp);
            strcat(coordinate, ", ");
            itoa(y, tmp, 10);
            strcat(coordinate, tmp);
            free(tmp);
            show_msgbox("Coordinate", coordinate);
            free(coordinate);
            wait_no_key_pressed();
            _reverse_pixel_(x, y);
            continue;
        }
        else continue;

        /* Backup Origin X, Y */
        int origin_x = x, origin_y = y;
        /* Move */
        switch (change) {
        case 1: 
            y--;
            break;
        case 2:
            x--;
            break;
        case 3:
            x++;
            break;
        case 4:
            y++;
            break;
        }
        /* Out of Range ? */
        if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
            x = origin_x;
            y = origin_y;
            sleep(100);
            continue;
        } else {
            _reverse_pixel_(origin_x, origin_y);
            _reverse_pixel_(x, y);
            sleep(100);
        }
    }
    _reverse_pixel_(x, y);
}
