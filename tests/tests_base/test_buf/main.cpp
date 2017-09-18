//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <zam/base/stream/streamInputBuf.h>
#include <zam/base/stream/streamOutputBuf.h>
#include <zam/base/buffer.h>

namespace base = zam::base;
namespace stream = zam::base::stream;

using buffer_t = base::buffer<4096>;
using istreambuf_t = stream::streamInputBuf<buffer_t>;
using ostreambuf_t = stream::streamOutputBuf<buffer_t>;

const auto DATA = "hello world!";
const auto DATA_LEN = 12; // strlen(DATA)

buffer_t g_buf;
void test_buf_write() {
    ostreambuf_t s(g_buf);
    s.write(DATA, DATA_LEN);

    std::cout << "o sizeBuf : " << s.bufferSize() << std::endl;
    std::cout << "o dataSize : " << s.dataSize() << std::endl;
    std::cout << "o writableSize : " << s.writableSize() << std::endl;
}

void test_buf_read() {
    istreambuf_t s(g_buf, DATA_LEN);
    std::cout << "i sizeBuf : " << s.bufferSize() << std::endl;
    std::cout << "i dataSize : " << s.dataSize() << std::endl;
    std::cout << "i readableSize : " << s.readableSize() << std::endl;

    char out[4096];
    memset(out, 0, sizeof(out));
    s.read(out, DATA_LEN);
    std::cout << "i out : " << out << std::endl;
    std::cout << "i readableSize : " << s.readableSize() << std::endl;
}

const auto DATA2 = "bye!";
const auto DATA2_LEN = 4; // strlen(DATA2)
void test_more_write() {
    istreambuf_t readStream(g_buf, DATA_LEN);
    ostreambuf_t outStream(readStream); /// create ostream from istream
    outStream.write(DATA2, DATA2_LEN);

    std::cout << "o2 sizeBuf : " << outStream.bufferSize() << std::endl;
    std::cout << "o2 dataSize : " << outStream.dataSize() << std::endl;
    std::cout << "o2 writableSize : " << outStream.writableSize() << std::endl;
}

void test_buf_read_from_writor() {
    ostreambuf_t outStream(g_buf, DATA_LEN+DATA2_LEN);
    istreambuf_t readStream(outStream); /// create istream from ostream

    std::cout << "i2 sizeBuf : " << readStream.bufferSize() << std::endl;
    std::cout << "i2 dataSize : " << readStream.dataSize() << std::endl;
    std::cout << "i2 readableSize : " << readStream.readableSize() << std::endl;

    char out[4096];
    memset(out, 0, sizeof(out));
    readStream.read(out, DATA_LEN+DATA2_LEN);
    std::cout << "i2 out : " << out << std::endl;
    std::cout << "i2 readableSize : " << readStream.readableSize() << std::endl;
}

void test_operators() {
    buffer_t buf;
    ostreambuf_t os(buf);
    os << (int)1;
    os << (float)3.14;
    os << std::string("hello");

    int v1;
    float v2;
    std::string v3;
    istreambuf_t is(os);

    is.readable(&v1, sizeof(v1));   /// this method doesn't move pointer
    std::cout << "readable test - " << v1 << std::endl;

    is >> v1 >> v2 >> v3;
    std::cout << "operator result - " << v1 << ", " << v2 << ", " << v3 << std::endl;
}

int main(int argc, char* argv[]) {

    test_buf_write();
    test_buf_read();
    test_more_write();
    test_buf_read_from_writor();
    test_operators();

    return 0;
}
