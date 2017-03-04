#include "ArgumentParser.hpp"
#include "HexagoScreenSaverConfig.hpp"
#include "HexagoScreenSaver.hpp"


namespace hexago {

    HexagoScreenSaverConfig parse_arguments(int argc, char* argv[]) {
        // just for the side effect, remove
        *argv[0] = argc;
        return HexagoScreenSaver::default_config();
    }

}
