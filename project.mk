# C source files
PROJECT_CSRC 	= main.c \
				 src/pwm_lld.c \
				 src/test_adc.c \
 				 src/uart_lld.c \
 				 src/servo.c \
 				 src/coord_transform.c \
 				 src/motor_control.c \

# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= inc

# Additional libraries
PROJECT_LIBS	=
# Compiler options
PROJECT_OPT     =  -lm -DCHPRINTF_USE_FLOAT=1

# Additional .mk files are included here
