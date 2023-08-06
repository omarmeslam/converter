

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define Rows  4
#define Cols  4

#define NO_KEY  'F'

#define FIRST_OUTPUT  PINB4
#define FIRST_INPUT   PIND2


#if KEYPAD_PRG
const u8 KeysArr[Rows][Cols]={{'7','8','9','A'},
			      {'4','5','6','B'},
			      {'1','2','3','C'},
			      {'Z','0','=','D'}};

#endif

#endif /* KEYPAD_CFG_H_ */
