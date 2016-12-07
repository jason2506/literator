from conans import ConanFile, CMake


class LiteratorConan(ConanFile):

    name = 'literator'
    version = '0.1.0'
    url = 'https://github.com/jason2506/literator'
    license = 'BSL-1.0'
    author = 'Chi-En Wu'

    settings = ('os', 'compiler', 'build_type', 'arch')
    generators = ('cmake', 'txt', 'env')

    exports = (
        'CMakeLists.txt',
        'cmake/*.cmake',
        'include/*.hpp',
    )

    def build(self):
        extra_opts = []

        cmake = CMake(self.settings)
        self.run('cmake "{src_dir}" {opts} {extra_opts}'.format(
            src_dir=self.conanfile_directory,
            opts=cmake.command_line,
            extra_opts=' '.join(extra_opts),
        ))
        self.run('cmake --build . {}'.format(cmake.build_config))

    def package(self):
        self.run('cmake --build . --target install')
