/**
 * test.cpp
 * A example of GetPx
 * @author Haruue Icymoon <Haruue Icymoon>
 * @version v1.0.1
 * @link https://github.com/haruue/GetPx_Ndless
 * @licence WTFPL
 */

#include <libndls.h>
#include "GetPx.h"

int main(void) {
    assert_ndless_rev(801);

    /* Use it wherever you want to get the coordinate. */
    get_px();
    
    return 0;
}
