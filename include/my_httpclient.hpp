// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#ifndef INCLUDE_MY_HTTPCLIENT_HPP_
#define INCLUDE_MY_HTTPCLIENT_HPP_

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>

int client_working(int argc, char* argv[]);

#endif  // INCLUDE_MY_HTTPCLIENT_HPP_
