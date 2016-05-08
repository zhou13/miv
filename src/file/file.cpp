#include "file/file.hpp"
#include "xarray/xarray.hpp"
#include "miv/miv.hpp"
#include "config/config.hpp"

File::File(Miv *miv, XArray *array, std::string filename) :
    m_miv(miv),
    m_array(array),
    m_filename(filename),
    m_config(new Config(ConfigLevel::FILE, miv->config()))
{
}

File::~File()
{
}

void File::read()
{
    FILE *fp = fopen(m_filename.c_str(), "rb");
    DIE_IF(!fp, "File {} cannot be opened", m_filename);

    fseek(fp, 0, SEEK_END);
    size_t file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    bool has_n = false;
    bool has_r = false;
    bool has_rn = false;

    wstring wstr;
    wstr.reserve(file_size);
    char *buffer = new char[file_size];
    fread(buffer, 1, file_size, fp);
    for (size_t i = 0; i < file_size; ++i) {
        switch (buffer[i]) {
        case '\r':
            if (i+1 < file_size && buffer[i+1] == '\n') {
                has_rn = true;
                ++i;
            } else {
                has_r = true;
            }
            wstr.push_back('\n');
            break;

        case'\n':
            has_n = true;
            wstr.push_back('\n');
            break;

        default:
            wstr.push_back(buffer[i]);
            break;
        }
    }

    /*
    std::string s("Hello World!\n"
                  "Hello!\n"
                  "World!\n"
                  "U\n"
                  "P\n"
                  "TTTT\n"
                  "T_T\n"
                  "This is the last line\n"
                  "This is really the last LINE!");
    */
    m_array->assign(wstr);

    if (has_n)
        config()->set("fileformat", "linux");
    else if (has_r)
        config()->set("fileformat", "mac");
    else if (has_rn)
        config()->set("fileformat", "windows");
    else
        config()->set("fileformat", "linux");
}


void File::write()
{
    // do nothing
}
