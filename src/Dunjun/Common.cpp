#include <Dunjun/Common.hpp>

#include <chrono>
#include <thread>

namespace Dunjun
{
std::string getFileDirectory(const std::string& filepath)
{
	usize found{filepath.find_last_of("/\\")};
	return filepath.substr(0, found);
}

namespace BaseDirectory
{
const std::string Textures{"data/textures/"};
const std::string Shaders{"data/shaders/"};
} // namespace BaseDirectory
} // namespace Dunjun
