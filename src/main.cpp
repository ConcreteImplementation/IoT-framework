#include <Arduino.h>

#include "Program.h"

Program* program;

void setup() {
	program = new Program(EST_DEBUG);
	program->setup();
}

void loop() {
  program->loop();
}