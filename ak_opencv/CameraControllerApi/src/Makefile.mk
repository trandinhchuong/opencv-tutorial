CXXFLAGS	+= -I./source/CameraControllerApi/src/

VPATH += source/CameraControllerApi/src


OBJ += $(OBJ_DIR)/Api.o
OBJ += $(OBJ_DIR)/Base64.o
OBJ += $(OBJ_DIR)/CameraController.o
OBJ += $(OBJ_DIR)/Server.o
OBJ += $(OBJ_DIR)/Settings.o
OBJ += $(OBJ_DIR)/Helper.o
OBJ += $(OBJ_DIR)/Command.o
OBJ += $(OBJ_DIR)/api_app.o

