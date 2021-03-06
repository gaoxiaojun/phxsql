/*
	Tencent is pleased to support the open source community by making PhxSQL available.
	Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
	Licensed under the GNU General Public License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
	
	https://opensource.org/licenses/GPL-2.0
	
	Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

#pragma once

#include <queue>
#include <vector>
#include <stdint.h>
#include <string>
#include <pthread.h>

namespace phxbinlog {

class Option;
class Storage {
 public:
    enum class MODE {
        WRITE = 1,
        READ = 2,
    };
 public:
    Storage(const MODE &mode, const std::string &datadir, const Option *option);
    ~Storage();

    int ReOpen(const std::string &path);
    int OpenDB(const std::string &path);
    int CloseDB();
    int FlushData();

    int WriteData(const std::string &data);
    int WriteData(const void *data, const size_t len);
    int ReadData(std::string *data);

    int SetFileReadPos(const std::string &path, const size_t &offset);
    int SetFileWritePos(const std::string &path, const size_t &offset, bool trunc = false);
    int Reset();

    size_t GetOffSet();
    std::string GetFileName();
    std::pair<std::string, size_t> GetFileInfo();

    void FSync();

 private:
    int SetFilePos(const std::string &path, const size_t &offset, const MODE &mode, bool trunc = false);
    void FixOffSet(size_t offset);
 private:
    int fd_;
    std::string path_, data_dir_;
    MODE mode_;
    const Option *option_;
};

}
