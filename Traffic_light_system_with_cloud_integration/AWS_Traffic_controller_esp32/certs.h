#include <pgmspace.h>

#define THINGNAME "******" // replace with thing name

const char WIFI_SSID[] = "*******"; // replace with wifi ssid              
const char WIFI_PASSWORD[] = "*******"; // replace with wifi password

const char AWS_IOT_ENDPOINT[] = "*************"; // replace with iot endpoint

// Amazon Root CA 1 : Replace yours
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
**********
)EOF";

// Device Certificate : Replace Yours
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
**********************

)KEY";

// Device Private key : Replace yours
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
****************


)KEY";
