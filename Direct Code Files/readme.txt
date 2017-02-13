As of 1/14/15
verison 1_2.c works, but count up function does not, must use the long method

As of 1/19/14
Individual functions have been moved to the functions folder and should be updated as they change.
Code version 1_2.c is still the current version
Things in the old folder are likely of little interest

As of 1/20/14
Code Version 1_5.c is the stable version. It now has working implemented Count up and Count Down features.
Known issues:
-PB8 and PB9 do not work as intended and have been manipulated to come out on PB0 and PB1, this
has allowed digit 3 to work.
-In update routine, up_0 has been replaced by set_0, as 0 sometimes comes directly after 5.
-In update routine, down_5 has been replaced by set_5 as 5 sometimes comes directly after 0.

As of 1/27/15
Code Version 1_6.c is the stable version. It has revised the up_0 and down_5 functions, and they
are implemented properly.
Known issues:
-PB8 and PB9 do not work as intended and have been manipulated to come out on PB0 and PB1, this
has allowed digit 3 to work.

As of 2/17/15
Code version 1_8.c is the stable version. It has a rudimentary keypad enter function implemented and working. Clock also moves faster due to change in pauses.

As of 3/3/15
Code version 1_11.c is the stable version. It has been commented and cleaned up significantly. Fast mode has been placed and debugged.
Keypad seems to be fully working, and unused buttons have been commented out successfully.
Known issues:
-PB8 and PB9 are still changed to PB0 and PB1, suspect they are tied to systick.
-Still needs timing
-Keypad allows more than 6 digits to be entered, and produces strange results above 6 digits.

As of 3/17/15
Code version 1_13.c is the stable version. It has timing implemented
Known issues:
-Seems to lose a second every 6 to 8 minutes. Likely due to updates overflowing, or similiar.
-PB8 and PB9 are still changed to PB0 and PB1, suspect they are tied to systick.
-Keypad allows more than 6 digits to be entered, and produces strange results above 6 digits.

As of 3/29/15
Code version 1_14.c is the current version.
Comments have been updated. Fast unexpected updates issue has been fixed.
Known issues:
-Was accurate to 1 sec an hour, but claims have been made to 2 seconds every 20 min.
-Reset is more reliable but inexplicably hangs system somethings
-PB8 and PB9 are still changed to PB0 and PB1, suspect they are tied to systick.
-Keypad allows more than 6 digits to be entered, and produces strange results above 6 digits.

As of 4/5/15
Code version 1_15.c is the current version.
Comments updates. Keypad no longer allows too many digits
Known issues:
-Was accurate to 1 sec an hour, but claims have been made to 2 seconds every 20 min.
-Reset no longer hangs system, but does not always trigger properly.
-PB8 and PB9 are still changed to PB0 and PB1, suspect they are tied to systick.

As of 4/26/15
Code version 1_16.c is the current version.
Comments updated. HSI source changed to HSE, system is accurate to +- 1.72seconds/day regardless
of temperature and board.
Known Issues:
-Reset no longer hangs system, but does not always trigger properly.
-PB8 and PB9 are still changed to PB0 and PB1, suspect they are tied to systick.

As of 4/27/15
Code version 1_17.c is the current version.
It has implemented a new keypad scan order to accommidate a change in keypad due to the failure
of the original.
Reset has been changed to purely a stop function but now works properly.

Code version 1_17_Original_keypad is identical to version 1_17.c except that it preserves the original
keypad layout and mapping.