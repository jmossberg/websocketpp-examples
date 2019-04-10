#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

using Client = websocketpp::client<websocketpp::config::asio_tls_client>;
using ConnectionHdl = websocketpp::connection_hdl;
using SslContext = websocketpp::lib::asio::ssl::context;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

void on_message(Client* client, ConnectionHdl hdl,
                websocketpp::config::asio_client::message_type::ptr msg) {
  std::cout << "on_message: " << msg->get_payload() << std::endl;
  client->close(hdl, websocketpp::close::status::normal, "done");
}

void on_open(Client* client, ConnectionHdl hdl) {
  std::string msg{"hello"};
  std::cout << "on_open: send " << msg << std::endl;
  client->send(hdl, msg, websocketpp::frame::opcode::text);
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

void set_open_handler(Client& client) {
  client.set_open_handler(websocketpp::lib::bind(&on_open, &client, ::_1));
}

void set_tls_init_handler(Client& client) {
  client.set_tls_init_handler(websocketpp::lib::bind(&on_tls_init));
}

void set_url(Client& client, std::string url) {
  websocketpp::lib::error_code ec;
  auto connection = client.get_connection(url, ec);
  client.connect(connection);
}

int main() {
  Client client;

  turn_off_logging(client);

  client.init_asio();

  set_tls_init_handler(client);
  set_open_handler(client);
  set_message_handler(client);

  set_url(client, "wss://localhost:30001");

  client.run();
}
