//
// Created by SungWoo Yang on 2017. 9. 2..
//

#include <boost/log/sinks/basic_sink_backend.hpp>
#include "loggerAppenderUdp.h"

#include "detail/frontendCreator.h"

#include "zam/base/log/detail/loggerWriter.h"

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr.hpp>

#include "external/JsonValueCaster/JsonValueCaster.h"

namespace asio = boost::asio;
namespace ip = asio::ip;
namespace logging = boost::log;
namespace sinks = boost::log::sinks;

namespace zam {
    namespace base {
        namespace log {

            // color print console backend
            class udp_ostream_backend : public boost::log::sinks::basic_formatted_sink_backend<char>
            {
            public:
                udp_ostream_backend(std::string url, uint16_t port)
                : socket_(io_service_, ip::udp::endpoint(ip::udp::v4(), 0))
                {
                    ip::udp::resolver resolver(io_service_);
                    ip::udp::resolver::query query(ip::udp::v4(), url, boost::lexical_cast<std::string>(port));
                    server_endpoint_ = *resolver.resolve(query);
                }

            public:
                void consume(boost::log::record_view const& rec, string_type const& formatted_string) {
                    try {
                        socket_.send_to(asio::buffer(formatted_string), server_endpoint_);
                    } catch(std::exception& e) {
                        std::cout << e.what() << std::endl;
                    }
                }

            private:
                asio::io_service io_service_;
                ip::udp::endpoint server_endpoint_;
                ip::udp::socket socket_;
            };

            void loggerAppenderUdp::load(loggerWriter &writer, Json::Value const &vAppender) {
                Json::CasterCoverDef const c(vAppender);
                auto const thisLevel = toLevel(c.get<std::string>("all", "level").c_str());
                auto const fmtType = toFormatType(c.get<std::string>("normal", "format").c_str());
                auto const url = c.get<std::string>("", "url");
                auto const port = c.get<uint16_t>(0, "port");

                if (url.empty() || !port)
                    throw std::runtime_error("invalid udp remote address info");

                Json::CasterBoolean jcb(vAppender);
                auto const isUnorder = jcb.get("unorder", false);

                auto backend = boost::make_shared<udp_ostream_backend>(url, port);

                auto creator = detail::frontendCreatorFactory::get(writer.getName(), backend, fmtType);

                creator->thisLevel = thisLevel;
                creator->isUnorder = isUnorder;
                auto sink = creator->generate();

                logging::core::get()->add_sink(sink);
                writer.addSink(sink);
            }

        }
    }
}
