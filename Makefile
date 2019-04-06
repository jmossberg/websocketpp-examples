CC=g++
CC_FLAGS=--std=c++17
INCLUDE_DIRS=-I$(HOME)/lib/boost/boost_1_67_0/include/ -I$(HOME)/src/websocketpp/websocketpp-0.8.1
LIB_FLAGS=-lpthread -L$(HOME)/lib/boost/boost_1_67_0/lib -lboost_system -lssl -lcrypto

websocketpp_client: websocketpp_client.cpp
	@echo Building target $@
	$(CC) $(CC_FLAGS) $(INCLUDE_DIRS) -o $@ $@.cpp $(LIB_FLAGS)

websocketpp_server: websocketpp_server.cpp
	@echo Building target $@
	$(CC) $(CC_FLAGS) $(INCLUDE_DIRS) -o $@ $@.cpp $(LIB_FLAGS)

websocketpp_chat_server: websocketpp_chat_server.cpp
	@echo Building target $@
	$(CC) $(CC_FLAGS) $(INCLUDE_DIRS) -o $@ $@.cpp $(LIB_FLAGS)

websocketpp_chat_client: websocketpp_chat_client.cpp
	@echo Building target $@
	$(CC) $(CC_FLAGS) $(INCLUDE_DIRS) -o $@ $@.cpp $(LIB_FLAGS)

websocketpp_examples: websocketpp_client websocketpp_server websocketpp_chat_server websocketpp_chat_client

run_client: websocketpp_client
	LD_LIBRARY_PATH=$(HOME)/lib/boost/boost_1_67_0/lib ./websocketpp_client

run_server: websocketpp_server
	LD_LIBRARY_PATH=$(HOME)/lib/boost/boost_1_67_0/lib ./websocketpp_server

run_chat_server: websocketpp_chat_server
	LD_LIBRARY_PATH=$(HOME)/lib/boost/boost_1_67_0/lib ./websocketpp_chat_server

run_chat_client: websocketpp_chat_client
	LD_LIBRARY_PATH=$(HOME)/lib/boost/boost_1_67_0/lib ./websocketpp_chat_client

clean:
	@echo Running target $@
	rm -f websocketpp_client
	rm -f websocketpp_server
	rm -f websocketpp_chat_server
	rm -f websocketpp_chat_client
