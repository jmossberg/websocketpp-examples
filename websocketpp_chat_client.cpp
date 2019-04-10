#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

using Client = websocketpp::client<websocketpp::config::asio_tls_client>;
using ConnectionHdl = websocketpp::connection_hdl;
using SslContext = websocketpp::lib::asio::ssl::context;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

void send_message(Client* client, ConnectionHdl* connection, std::string msg) {
  client->send(*connection, msg, websocketpp::frame::opcode::text);
}

void close_connection(Client* client, ConnectionHdl* connection) {
  client->close(*connection, websocketpp::close::status::normal, "done");
}

void on_message(Client* client, ConnectionHdl hdl,
                websocketpp::config::asio_client::message_type::ptr msg) {
  std::cout << "< " << msg->get_payload() << std::endl;
}

void on_open(Client* client, ConnectionHdl* connection, ConnectionHdl hdl) {
  *connection = hdl;
}

websocketpp::lib::shared_ptr<SslContext> on_tls_init() {
  auto ctx = websocketpp::lib::make_shared<SslContext>(
      boost::asio::ssl::context::sslv23);
  return ctx;
}

void turn_off_logging(Client& client) {
  client.clear_access_channels(websocketpp::log::alevel::all);
  client.clear_error_channels(websocketpp::log::elevel::all);
}

void set_message_handler(Client& client) {
  client.set_message_handler(
      websocketpp::lib::bind(&on_message, &client, ::_1, ::_2));
}

void set_open_handler(Client& client, ConnectionHdl* connection) {
  client.set_open_handler(
      websocketpp::lib::bind(&on_open, &client, connection, ::_1));
}

void set_tls_init_handler(Client& client) {
  client.set_tls_init_handler(websocketpp::lib::bind(&on_tls_init));
}

void set_url(Client& client, std::string url) {
  websocketpp::lib::error_code ec;
  auto connection = client.get_connection(url, ec);
  client.connect(connection);
}

int main(int argc, char* argv[]) {
  bool done = false;
  std::string input;
  std::string name;
  Client client;
  ConnectionHdl connection;

  turn_off_logging(client);

  client.init_asio();

  set_tls_init_handler(client);
  set_open_handler(client, &connection);
  set_message_handler(client);

  set_url(client, "ws://localhost:30001");

  websocketpp::lib::thread t1(&Client::run, &client);

  std::cout << "Name: ";
  std::getline(std::cin, name);

  while (!done) {
    std::getline(std::cin, input);
    if (input == "close") {
      done = true;
      close_connection(&client, &connection);
    } else if (input == "help") {
      std::cout << "\nCommand List:\n"
                << "close\n"
                << "send <message>\n"
                << "help: Display this help text\n"
                << std::endl;
    } else {
      std::string msg{name + ": " + input};
      send_message(&client, &connection, msg);
    }
  }

  t1.join();
}
