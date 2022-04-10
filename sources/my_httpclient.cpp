// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#include "my_httpclient.hpp"

int client_working(int argc, char* argv[]) {
  try
  {
    // Check command line arguments.
    if (argc != 5)
    {
      std::cerr << "Usage: http-client-sync <host> <port> <target> "
                   "<request>\n"
                << "Example:\n"
                   "http-client-sync localhost 8080 /v1/api/suggest "
                << R"({"input":"<user_input>"})";
      return EXIT_FAILURE;
    }
    auto const host = argv[1];
    auto const port = argv[2];
    auto const target = argv[3];
    auto const request = argv[4];
    int version = 11;
    std::cout << host << " " << port << " " << target << " " <<  request
              << std::endl;
    // The io_context is required for all I/O
    net::io_context ioc;

    // These objects perform our I/O
    net::ip::tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);

    // Look up the domain name
    auto const results = resolver.resolve(host, port);

    // Make the connection on the IP address we get from a lookup
    stream.connect(results);

    http::string_body::value_type body = request;

    // Set up an HTTP GET request message
    http::request<http::string_body> req{http::verb::post, target, version};
    req.set(http::field::host, host);
    req.body() = body;
    req.prepare_payload();
    req.set(http::field::content_type, "text/html");
    // Send the HTTP request to the remote host
    http::write(stream, req);

    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    http::read(stream, buffer, res);

    // Write the message to standard out
    std::cout << res << std::endl;

    // Gracefully close the socket
    beast::error_code ec;
    stream.socket().shutdown(net::ip::tcp::socket::shutdown_both, ec);

    // not_connected happens sometimes
    // so don't bother reporting it.
    //
    if (ec && ec != beast::errc::not_connected)
      throw beast::system_error{ec};

    // If we get here then the connection is closed gracefully
  }
  catch(std::exception const& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
