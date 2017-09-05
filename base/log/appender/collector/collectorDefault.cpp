//
// Created by SungWoo Yang on 2017. 9. 5..
//

#include "base.h"
#include "collectorDefault.h"

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/conversion.hpp>

namespace zam {
    namespace base {
        namespace log {
            namespace collector {

                collectorDefault::collectorDefault(std::string filename, std::string path_root)
                        : filename_(filename), path_root_(path_root) {
                }

                void collectorDefault::store_file(boost::filesystem::path const &src_path) {
                    moveStoreFile(src_path);
                }

                uintmax_t collectorDefault::scan_for_files(
                        boost::log::sinks::file::scan_method method,
                        boost::filesystem::path const &pattern, unsigned int *counter) {
                    uintmax_t found_cnt = 0;

                    const std::string target_path(path_root_);

                    boost::filesystem::directory_iterator end_itr;
                    for (boost::filesystem::directory_iterator i(target_path); i != end_itr; ++i) {
                        if (!boost::filesystem::is_regular_file(i->status()))
                            continue;

                        if (!i->path().has_filename())
                            continue;

                        //if (std::string::npos == i->path().generic_string().find(filename_))
                        //    continue;

                        moveStoreFile(i->path());
                        ++found_cnt;
                    }

                    return found_cnt;
                }

                void collectorDefault::moveStoreFile(boost::filesystem::path const &src_path) {
                    try {
                        auto clock = boost::posix_time::to_tm(
                                boost::posix_time::from_time_t(
                                        boost::filesystem::last_write_time(
                                                src_path.generic_string().c_str()
                                        )
                                )
                        );

                        std::string path_backup_root = (boost::format("%s/%04d%02d%02d")
                                                        % path_root_.c_str()
                                                        % (clock.tm_year + 1900) % (clock.tm_mon + 1) %
                                                        clock.tm_mday).str();

                        std::string path_backup_full = path_backup_root + "/" + src_path.filename().generic_string();
                        if (boost::filesystem::exists(path_backup_full)) {
                            int old_idx = 0;
                            while (old_idx < 10000) {
                                std::ostringstream ss_old;
                                ss_old << path_backup_full << "_" << old_idx;

                                if (boost::filesystem::exists(ss_old.str())) {
                                    ++old_idx;
                                    continue;
                                }

                                boost::filesystem::rename(path_backup_full, ss_old.str());
                                break;
                            }

                            if (boost::filesystem::exists(path_backup_full))
                                boost::filesystem::remove(path_backup_full);
                        }

                        boost::filesystem::create_directories(boost::filesystem::path(path_backup_root));
                        boost::filesystem::rename(src_path, boost::filesystem::path(path_backup_full));
                    }
                    catch (std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    catch (...) {
                        std::cerr << "failed to store a log file : " << src_path << std::endl;
                    }
                }


            }
        }

    }
}