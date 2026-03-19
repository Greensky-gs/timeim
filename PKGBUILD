pkgname=timeim
pkgver=1.0.0
pkgrel=1
pkgdesc="A simple command to nicely display the time in the terminal"
arch=('x86_64')
url="https://github.com/Greensky-gs/timeim"
license=('GPL3')
depends=()
makedepends=('gcc')

source=("${pkgname}-${pkgver}.tar.gz")
sha256sums=('SKIP')

build() {
    cd "${srcdir}/${pkgname}-${pkgver}"
    make all
}

package() {
    cd "${srcdir}/${pkgname}-${pkgver}"
    make PREFIX=/usr DATADIR=/usr/share/${pkgname} DESTDIR="${pkgdir}" install
}

