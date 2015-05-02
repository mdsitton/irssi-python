pkgname=irssi-python-git
pkgver=r34.78a3f49
pkgrel=1
pkgdesc="Provides Python scripting support for irssi"
url="http://irssi.org"
arch=('x86_64' 'i686')
depends=('python2')
license=('GPL2')
makedepends=('git' 'libtool' 'automake' 'autoconf')
source=('http://www.irssi.org/files/irssi-0.8.17.tar.gz'
        "${pkgname}::git://github.com/mdsitton/irssi-python.git")

md5sums=('00cde2ba7ba37af9e3df451f430ecdea'
         'SKIP')

pkgver() {
    cd "$srcdir/$pkgname"
    printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

prepare() {
    tar -zxf 0.8.17.tar.gz
}

build() {
    # The following line makes "configure" look for python2 instead of python,
    # since python on Arch refers to Python 3, which would cause an error.
    export PYTHON_VERSION=2
    cd "$srcdir/$pkgname"
    awk -f src/constants.awk src/constants.txt > src/pyconstants.c
    libtoolize -f -c
    aclocal --force -I.
    autoheader -f
    autoconf -f
    automake -a -c --gnu --foreign
    ./configure --with-irssi=../irssi-0.8.17 --datadir=/usr --prefix=/usr --localstatedir=/var --sysconfdir=/etc

    make -C src constants
    make
}

package() {
    # libpython.so will be installed in /usr/lib/irssi/modules
    # Scripts will be installed in /usr/share/irssi/scripts
    # Documentation will be installed in /usr/share/doc/irssi
    cd "$srcdir/$pkgname"
    mkdir -p "$pkgdir/usr/share/doc/irssi"
    install -m644 "docs/irssi-python.html" "$pkgdir/usr/share/doc/irssi"
    make DESTDIR="$pkgdir" install
}