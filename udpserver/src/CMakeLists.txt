# 指定源文件路径
SET(SRC_LIST udpServer.cpp main.cpp)

# 指定头文件路径
INCLUDE_DIRECTORIES("../inc")

# 指定生成目标
ADD_EXECUTABLE(udpserver ${SRC_LIST})