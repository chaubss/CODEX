#include "ptable_reader.h"
#include <iostream>
using namespace std;

int main() {

    ParsingTableReader *p = new ParsingTableReader("actions.csv", "goto.csv");

    return 0;
}