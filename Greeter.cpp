#include <iostream>
#include "Greeter.h"

using namespace std;

Greeter::Greeter() {
    filterManager = new FilterManager();
    imageManager = new ImageManager(this->filterManager);
}

Greeter::~Greeter() {
    delete imageManager;
    delete filterManager;
}

void Greeter::run() {
    int input;
    printLogo();
    
    while (true) {
        printf("\n");
        printf("+-------------------+\n");
        printf("| Main Menu         |\n");
        printf("+-------------------+\n");
        printf("| # | Menu          |\n");
        printf("+---+---------------+\n");
        printf("| 1 | Manage filter |\n");
        printf("| 2 | Manage image  |\n");
        printf("| 0 | Quit          |\n");
        printf("+---+---------------+\n");
        cout << "Select menu >> ";
        
        cin >> input;
        
        switch (input) {
            case 1:
                filterManager->run();
                break;
            case 2:
                imageManager->run();
                break;
            case 0:
                cout << "Bye" << endl;
                return;
            default:
                cout << "Wrong menu number!" << endl;
                break;
        }
    }
}

void Greeter::printLogo() {
    cout << " ######  ##   ##   ####    ####   ######      ######  ######  ##      ######  ######  #####  " << endl;
    cout << "   ##    ### ###  ##  ##  ##      ##          ##        ##    ##        ##    ##      ##  ## " << endl;
    cout << "   ##    ## # ##  ######  ## ###  ####        ####      ##    ##        ##    ####    #####  " << endl;
    cout << "   ##    ##   ##  ##  ##  ##  ##  ##          ##        ##    ##        ##    ##      ##  ## " << endl;
    cout << " ######  ##   ##  ##  ##   ####   ######      ##      ######  ######    ##    ######  ##  ##." << endl;
}
