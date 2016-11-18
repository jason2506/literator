from conans import ConanFile, CMake


class DesaConan(ConanFile):

    name = 'literator'
    version = '0.1.0'
    url = 'https://github.com/jason2506/literator'
    license = 'BSL-1.0'
    author = 'Chi-En Wu'

    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'cmake'

    exports = (
        'CMakeLists.txt',
        'cmake/*.cmake',
        'include/*.hpp',
    )

    def build(self):
        cmake = CMake(self.settings)
        self.run('cmake "%s" %s' % (
            self.conanfile_directory,
            cmake.command_line
        ))

    def package(self):
        self.copy('*.cmake', dst='', src='cmake')
        self.copy('*.hpp', dst='include', src='include')
