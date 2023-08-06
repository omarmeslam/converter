

#ifndef CONVERTER_Interface_H_
#define CONVERTER_Interface_H_

void Converter_Init(void);
void Converter_Runnable(void);

#define  DECIMAL  '1'
#define  BINARY   '2'
#define  HEX      '3'

typedef enum{
	step_1=1,
	step_2,
	step_3
	}OperationSteps_type;

#endif /* CONVERTER_Interface_H_ */