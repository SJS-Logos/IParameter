import os
import re
from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMake, CMakeToolchain, cmake_layout
from conan.tools import files
from conan.tools.files.symlinks import absolute_to_relative_symlinks
from conan.tools.files import copy
from pathlib import Path

class PricingAlgorithmRecipe(ConanFile):
    name = 'pricingalgorithm'
    
    author = 'jea@logos.dk'
    
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'CMakeDeps'
    package_type = 'static-library'
    
    options = {
        'shared': [True, False], 'fPIC': [True, False], 'exportSource': [True, False]
    }
    default_options = {
        'shared': False, 'fPIC': True, 'exportSource': False
    }
    
    exports_sources = 'CMakeLists.txt', 'src/*', 'tests/*', 'cmake/*'
    
    def set_version(self):
        lines = files.load(self, os.path.join(self.recipe_folder, "src", "version.h")).splitlines()
        for line in lines:
            result = re.search('#define VERSION "(.*)"', line)
            if result:
                self.version = result.groups()[0]
                break
    
    def requirements(self):
        self.requires('osinterface/[>=1]')
        self.requires('osutil/[>=1]')
        self.requires('logostext/[>=1]')
    
    
        self.test_requires('gtest/1.13.0')
        self.test_requires('idebugdummy/[>=1]')
        
        self.tool_requires('logosbashscripts/[>1]')
        self.tool_requires('logoscmakescripts/[>1]')
    
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
    
    def layout(self):
        cmake_layout(self)
        self.folders.build = "conan/build"
        self.folders.generators = "conan"
    
    def generate(self):
        tc = CMakeToolchain(self)
        tc.presets_prefix = Path(self.folders._base_build).name
        tc.generate()
        for require in self.dependencies.values():
            copy(self, "bash/*", require.package_folder, self.source_folder, keep_path=True)
            copy(self, "cmake/*", require.package_folder, self.source_folder, keep_path=True)
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        #cmake.test()
        self.run("ctest -VV --output-junit testRes.xml")
    
    def package(self):
        cmake = CMake(self)
        cmake.install()
        if self.options.exportSource:
            sources = os.path.join(self.export_sources_folder, "src")
            files.copy(self, pattern="*", src=sources, dst=os.path.join(self.package_folder, "src"), keep_path=True)
            absolute_to_relative_symlinks(self, self.package_folder)
    
    @property
    def _postfix(self):
        if self.settings.os == "Windows":
            return "d" if self.settings.build_type == "Debug" else ""
    
    def package_info(self):
        self.cpp_info.libs = ["PricingAlgorithm"]
        self.cpp_info.set_property("cmake_find_mode", "none")  # do not generate find modules
        self.cpp_info.builddirs.append(os.path.join("lib", "cmake", "PricingAlgorithm"))
        self.cpp_info.set_property("cmake_file_name", "PricingAlgorithm")
        self.cpp_info.set_property("cmake_target_name", "Logos::PricingAlgorithm")