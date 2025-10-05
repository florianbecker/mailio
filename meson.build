project('mailio', 'cpp',
  version: '0.26.0',             # Angepasste Versionsnummer (basierend auf dem Repo-Status)
  license: 'BSL-1.0',            # Boost Software License
  default_options: ['cpp_std=c++17', 'warning_level=2']) # C++17 Standard setzen

# compiler used by multiple subdirectories
compiler = meson.get_compiler('cpp')
if build_machine.system() == 'darwin'
  add_languages('objcpp', native: false)
  add_global_arguments('-U_LIBCPP_ENABLE_ASSERTIONS', language : 'cpp')
  add_global_arguments('-D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_FAST', language : 'cpp')
endif

# Boost: Hauptabhängigkeit für asio (Networking), system und ggf. weitere
# Wir verwenden die 'system' Komponente, die oft für asio-basierte Projekte benötigt wird.
## boost dependencies
boost_version = '>=1.81.0'
boost_dependency = dependency('boost')
boost_filesystem_dependency = dependency(
  'boost',
  version: boost_version,
  modules: ['filesystem'],
  static: true
)
#boost_dep = dependency('boost', modules: ['system'], required: true)

# OpenSSL/LibreSSL: Notwendig für die sichere Kommunikation (SMTPS, IMAPS, POP3S)
ssl_dep = dependency('openssl', required: true)

# Pfad zu den öffentlichen Header-Dateien (z.B. include/mailio/message.hpp)
mailio_inc = include_directories('include')

# Quelldateien für die Mailio-Bibliothek (basierend auf dem /src Verzeichnis)
# Wir verwenden files() für eine statische Liste der CPP-Dateien.
mailio_src = files(
  'src/base64.cpp',
  'src/binary.cpp',
  'src/bit7.cpp',
  'src/bit8.cpp',
  'src/codec.cpp',
  'src/dialog.cpp',
  'src/imap.cpp',
  'src/mailboxes.cpp',
  'src/message.cpp',
  'src/mime.cpp',
  'src/percent.cpp',
  'src/pop3.cpp',
  'src/quoted_printable.cpp',
  'src/q_codec.cpp',
  'src/smtp.cpp'
)

# Erstellung der Shared Library (libmailio.so/.dylib/.dll)
mailio_lib = library('mailio',
  mailio_src,
  include_directories: mailio_inc,
  dependencies: [boost_dependency, ssl_dep],
  cpp_args: ['-DBOOST_ALL_NO_LIB'], # Optional: Kann Linker-Probleme mit Boost beheben
  install: true                     # Die Bibliothek soll installiert werden
)

# Installation der Header-Dateien in das System-Include-Verzeichnis
install_subdir('include/mailio', install_dir: 'include')

# Generiert eine .pc-Datei, damit andere Meson/CMake Projekte mailio leicht finden
pkgconfig = import('pkgconfig')
pkgconfig.generate(
  libraries: mailio_lib,
  subdirs: ['mailio'], # Wo die Header nach der Installation zu finden sind
  name: 'mailio',
  description: 'A simple and modern C++ library for MIME message and mail transfer support.',
  version: meson.project_version()
)
