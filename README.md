# websocketpp-examples<a name="websocketpp-examples"></a>
Examples using WebSocket++ C++ header only library

1. Minimalistic client and server
1. Command line based chat client and server

# Contents<a name="contents"></a>

* [How to build WebSocket++ examples](#how-to-build-websocket++-examples)
    * [Alternative 1: Using Docker](#alternative-1-using-docker)
    * [Alternative 2: Native on Ubuntu 18.04](#alternative-2-native-on-ubuntu-1804)
* [How to run WebSocket++ examples](#how-to-run-websocket++-examples)

# How to build WebSocket++ examples<a name="how-to-build-websocket++-examples"></a>

## Alternative 1: Using Docker<a name="alternative-1-using-docker"></a>

1. Install Docker: https://docs.docker.com/install/

1. Clone this repository

        $ cd ~/git
        $ git clone https://github.com/jmossberg/websocketpp-examples.git
        $ cd websocketpp-examples

1. Make shell scripts executable

        $ chmod +x *.sh

1. Build docker image with name `docker_websocketpp`

        $ ./docker_websocketpp.sh build

## Alternative 2: Native on Ubuntu 18.04<a name="alternative-2-native-on-ubuntu-1804"></a>

1. Clone this repository

        $ cd ~/git
        $ git clone https://github.com/jmossberg/websocketpp-examples.git
        $ cd websocketpp-examples

1. Make shell scripts executable

        $ chmod +x *.sh

1. Install tools

        $ sudo ./install_tools.sh

1. Install boost

        $ ./install_boost.sh 1.67.0

1. Download WebSocket++

        $ ./download_websocketpp.sh 0.8.1

1. Create certificate to enable TLS encryption

        $ ./create_certificate.sh

1. Build examples

        $ make websocketpp_examples 

# How to run WebSocket++ examples<a name="how-to-run-websocket++-examples"></a>

The examples below assume alternative 1 above was used, i.e. using Docker. Running the examples without Docker is similar. Just skip the commands that involve the `docker_websocketpp.sh` script.

1. Start docker container and start the minimalistic server

        $ ./docker_websocketpp.sh run
        $ make run_server

1. Open a second Terminal

1. Connect to the docker container and start the minimalistic client

        $ ./docker_websocketpp.sh connect_shell
        $ make run_client

1. Output from server

        cpp_user@0516a15f6c07:~/websocketpp_examples$ make run_server
        LD_LIBRARY_PATH=/home/cpp_user/lib/boost/boost_1_67_0/lib ./websocketpp_server
        on_message: hello

1. Output from client

        cpp_user@0516a15f6c07:~/websocketpp_examples$ make run_client
        LD_LIBRARY_PATH=/home/cpp_user/lib/boost/boost_1_67_0/lib ./websocketpp_client
        on_open: send hello
        on_message: hello
        cpp_user@0516a15f6c07:~/websocketpp_examples$ 

1. Now let's try the chat server and chat client

1. Go back to the first Terminal which runs the server and hit Ctrl-C, then start the chat server.

        $ make run_chat_server

1. Go to the second Terminal and start a client

        $ make run_chat_client

1. Enter a name

        Name: Anna

1. Open a third Terminal and connect a second client

        $ ./docker_websocketpp.sh connect_shell
        $ make run_chat_client

1. Enter another name and a message

        Name: Elsa
        hello from Elsa

1. Go back to the second Terminal and enter a message from Anna

        hello from Anna

1. You can terminate the client by entering the command `close`.

1. Output from chat server

        cpp_user@0516a15f6c07:~/websocketpp_examples$ make run_chat_server
        LD_LIBRARY_PATH=/home/cpp_user/lib/boost/boost_1_67_0/lib ./websocketpp_chat_server
        on_open
        connections: 1
        on_open
        connections: 2
        on_message: Elsa: hello from Elsa
        on_message: Anna: hello from Anna

1. Output from first chat client

        on_message: hello
        cpp_user@0516a15f6c07:~/websocketpp_examples$ make run_chat_client
        LD_LIBRARY_PATH=/home/cpp_user/lib/boost/boost_1_67_0/lib ./websocketpp_chat_client
        Name: Anna
        < Elsa: hello from Elsa
        hello from Anna

1. Output from second chat client

        cpp_user@0516a15f6c07:~/websocketpp_examples$ make run_chat_client
        LD_LIBRARY_PATH=/home/cpp_user/lib/boost/boost_1_67_0/lib ./websocketpp_chat_client
        Name: Elsa
        hello from Elsa
        < Anna: hello from Anna

