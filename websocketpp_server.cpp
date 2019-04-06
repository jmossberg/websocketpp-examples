#include <csignal>
#include <iostream>
#include <websocketpp/config/asio.hpp>
#include <websocketpp/server.hpp>

using Server = websocketpp::server<websocketpp::config::asio_tls>;
using ConnectionHdl = websocketpp::connection_hdl;
using SslContext = websocketpp::lib::asio::ssl::context;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

void on_message(Server* server, ConnectionHdl hdl,
                websocketpp::config::asio::message_type::ptr msg) {
  std::cout << "on_message: " << msg->get_payload() << std::endl;
  server->send(hdl, msg->get_payload(), websocketpp::frame::opcode::text);
}

websocketpp::lib::shared_ptr<SslContext> on_tls_init(ConnectionHdl hdl) {
  auto ctx = websocketpp::lib::make_shared<SslContext>(SslContext::sslv23);

  ctx->use_certificate_chain_file("cert.pem");
  ctx->use_private_key_file("key.pem", SslContext::pem);
  return ctx;
}

void turn_off_logging(Server& server) {
  server.clear_access_channels(websocketpp::log::alevel::all);
  server.clear_error_channels(websocketpp::log::elevel::all);
}

void set_message_handler(Server& server) {
  server.set_message_handler(
      websocketpp::lib::bind(&on_message, &server, ::_1, ::_2));
}

void set_tls_init_handler(Server& server) {
  server.set_tls_init_handler(websocketpp::lib::bind(&on_tls_init, ::_1));
}

int main() {
  Server server;

  turn_off_logging(server);

  server.init_asio();

  set_message_handler(server);
  set_tls_init_handler(server);

  server.listen(30001);
  server.start_accept();
  server.run();
}