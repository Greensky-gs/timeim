pkgname=timeim
_name=timeim
pkgver=1.0.0
pkgrel=2
pkgdesc="A simple command to nicely display the time in the terminal"
arch=('x86_64')
url="https://github.com/Greensky-gs/timeim"
license=('GPL3')
depends=()
makedepends=('gcc' 'git' 'make')
source=("git+${url}#commit=9664169a83282d928a41da3d0df1c4bd80303a3b")
options=("!debug")
sha256sums=('SKIP')

build() {
  cd "$srcdir/$_name"
  make all
}

package() {
  cd "${srcdir}/$_name"
  make PREFIX=/usr DATADIR=/usr/share/${pkgname} DESTDIR="${pkgdir}" install
}
