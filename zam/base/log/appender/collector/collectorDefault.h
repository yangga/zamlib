//
// Created by SungWoo Yang on 2017. 9. 5..
//

#ifndef ZAMLIB_COLLECTORDEFAULT_H
#define ZAMLIB_COLLECTORDEFAULT_H

#include <boost/log/sinks/text_file_backend.hpp>

namespace zam {
    namespace base {
        namespace log {
            namespace collector {

                class collectorDefault
                        : public boost::log::sinks::file::collector
                {
                public:
                    collectorDefault(std::string filename, std::string path_root);

                    void store_file(boost::filesystem::path const &src_path) override;
                    uintmax_t scan_for_files(
                            boost::log::sinks::file::scan_method method,
                            boost::filesystem::path const &pattern = boost::filesystem::path(), unsigned int *counter = 0) override;

                private:
                    void moveStoreFile(boost::filesystem::path const &src_path);

                private:
                    std::string path_root_;
                    std::string filename_;
                };

            }
        }
    }
}


#endif //ZAMLIB_COLLECTORDEFAULT_H
