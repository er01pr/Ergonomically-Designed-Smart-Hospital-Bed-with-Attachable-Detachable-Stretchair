// millisDelay.cpp

/*
 * (c)2018 Forward Computing and Control Pty. Ltd.
 * NSW Australia, www.forward.com.au
 * This code is not warranted to be fit for any purpose. You may only use it at your own risk.
 * This generated code may be freely used for both private and commercial use
 * provided this copyright is maintained.
 */

// include Arduino.h for millis()
#include <Arduino.h>
#include <millisDelay.h>

millisDelay::millisDelay() {
  running = false; // not running on start
  startTime = 0; // not started yet
  finishNow = false; // do not finish early
}

/**
   Start a delay of this many milliseconds
   @param delay in millisconds, 0 means isFinished() will return true on first call
*/
void millisDelay::start(unsigned long delay) {
  mS_delay = delay;
  startTime = millis();
  running = true;
  finishNow = false; // do not finish early
}

/**
   Stop the delay
   isFinished() will now never return true
   until after start(),restart() or repeat() called again
*/
void millisDelay::stop() {
  running = false;
  finishNow = false; // do not finish early
}

/**
   repeat()
   Do same delay again but allow for a possible delay in calling isFinished()
*/
void millisDelay::repeat() {
  startTime = startTime + mS_delay;
  running = true;
  finishNow = false; // do not finish early
}

/**
   restart()
   Start the same delay again starting from now
   Note: use repeat() when isFinished() returns true, if you want a regular repeating delay
*/
void millisDelay::restart() {
  start(mS_delay);
}

/**
   Force delay to end now
*/
void millisDelay::finish() {
  finishNow = true; // finish early
}

/**
  Has the delay ended/expired or has finish() been called?
  isFinished() returns true just once when delay first exceeded or the first time it is called after finish() called
*/
bool millisDelay::isFinished() {
  if (running && (finishNow || ((millis() - startTime) >= mS_delay))) {
    stop();
    return true;
  } // else {
  return false;
}

/**
  Is the delay running, i.e. isFinished() will return true at some time in the future
*/
bool millisDelay::isRunning() {
  return running;
}

/**
  Returns the last time this delay was started, in mS, by calling start(), repeat() or restart()
  Returns 0 if it has never been started
*/
unsigned long millisDelay::getStartTime() {
	return startTime;
}

/**
  How many mS remaining until delay finishes
  Returns 0 if isFinished() returned true or stop() called
*/
unsigned long millisDelay::remaining() {
  if (running) {
    unsigned long mS = millis(); // capture current millis() as it may tick over between uses below
    if (finishNow || ((mS - startTime) >= mS_delay)) {  // check if delay exceeded already but isFinished() has not been called yet
      return 0;
    } else {
      return (mS_delay - (mS - startTime));
    }
  } else { // not running. stop() called or isFinished() returned true
    return 0;
  }
}

/**
  The delay set in mS set in start
*/
unsigned long millisDelay::delay() {
  return mS_delay;
}
