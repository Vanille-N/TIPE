#include "flowdisplayer.h"

FlowDisplayer::FlowDisplayer (QWidget * parent, State * Stt) {
    setFixedSize(150, 350) ;
    m_Stt = Stt ;
    connect(parent, SIGNAL(refresh()), this, SLOT(refresh())) ;
    m_vbox = new QVBoxLayout ;
    setParent(parent) ;
    m_lcdPhi = new QLCDNumber (this) ;
    m_lcdAlpha = new QLCDNumber (this) ;
    m_lcdBeta = new QLCDNumber (this) ;
    m_lcdDelta = new QLCDNumber (this) ;
    m_lcdTrans = new QLCDNumber (this) ;
    m_lcdPhi->setSmallDecimalPoint(true) ;
    m_lcdAlpha->setSmallDecimalPoint(true) ;
    m_lcdBeta->setSmallDecimalPoint(true) ;
    m_lcdDelta->setSmallDecimalPoint(true) ;
    m_lcdTrans->setSmallDecimalPoint(true) ;
    m_lcdPhi->setDigitCount(7) ;
    m_lcdAlpha->setDigitCount(7) ;
    m_lcdBeta->setDigitCount(7) ;
    m_lcdDelta->setDigitCount(7) ;
    m_lcdTrans->setDigitCount(7) ;
    m_lcdPhi->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcdAlpha->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcdBeta->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcdDelta->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcdTrans->setSegmentStyle(QLCDNumber::Flat) ;
    m_lcdPhi->setAutoFillBackground(true) ;
    m_lcdAlpha->setAutoFillBackground(true) ;
    m_lcdBeta->setAutoFillBackground(true) ;
    m_lcdDelta->setAutoFillBackground(true) ;
    m_lcdTrans->setAutoFillBackground(true) ;
    m_lcdPhi->setToolTip("Flux (dimentionné) :\nϕ = λ ρ₀ [-α(Tₚ - Tₑ) + β(Sₚ - Sₑ)]");
    m_lcdAlpha->setToolTip("Forçage (adimentionné) :\nα' = 2 (τₜ / M₀) λ ρ₀ α (Tₑ* - Tₚ*)") ;
    m_lcdBeta->setToolTip("β' = 2 (τₜ / M₀) λ ρ₀ β (Sₑ* - Sₚ*)") ;
    m_lcdDelta->setToolTip("δ' = τₜ / τₛ") ;
    m_lcdTrans->setToolTip("Flux (adimentionné) :\nϕ' = 2 (τₜ / M₀) ϕ") ;
    QPalette Pal = m_lcdPhi->palette() ;
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::black) ;
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::white) ;
    m_lcdPhi->setPalette(Pal) ;
    m_lcdAlpha->setPalette(Pal) ;
    m_lcdBeta->setPalette(Pal) ;
    m_lcdDelta->setPalette(Pal) ;
    m_lcdTrans->setPalette(Pal) ;

    m_lcdPhi->display(m_Stt->getPhi()) ;
    m_lcdAlpha->display(0) ;
    m_lcdBeta->display(0) ;
    m_lcdDelta->display(0) ;
    m_lcdTrans->display(0) ;

    m_surfaceFlow = new QLabel (FLOWRT, this) ;
    m_deepFlow = new QLabel (FLOWLT, this) ;
    m_surfaceFlow->setAlignment(Qt::AlignCenter) ;
    m_deepFlow->setAlignment(Qt::AlignCenter) ;
    m_surfaceFlow->setFont(QFont("helvetica", 20, QFont::Bold)) ;
    m_deepFlow->setFont(QFont("helvetica", 20, QFont::Bold)) ;
    auto alphabox = new QHBoxLayout () ;
    auto gammabox = new QHBoxLayout () ;
    auto deltabox = new QHBoxLayout () ;
    auto phibox = new QHBoxLayout () ;
    alphabox->addWidget(new QLabel ("   α'", this), 1) ;
    gammabox->addWidget(new QLabel ("   β'", this), 1) ;
    deltabox->addWidget(new QLabel ("   δ'", this), 1) ;
    phibox->addWidget(new QLabel ("   ϕ'", this), 1) ;
    alphabox->addWidget(m_lcdAlpha, 5) ;
    gammabox->addWidget(m_lcdBeta, 5) ;
    deltabox->addWidget(m_lcdDelta, 5) ;
    phibox->addWidget(m_lcdTrans, 5) ;
    m_vbox->addWidget(m_surfaceFlow) ;
    m_vbox->addWidget(new QLabel ("   ϕ", this)) ;
    m_vbox->addWidget(m_lcdPhi) ;
    m_vbox->addLayout(alphabox) ;
    m_vbox->addLayout(gammabox) ;
    m_vbox->addLayout(deltabox) ;
    m_vbox->addLayout(phibox) ;
    m_vbox->addWidget(m_deepFlow) ;

    setLayout(m_vbox) ;
}

void FlowDisplayer::refresh () {
    double phi = m_Stt->getPhi() ;
    m_lcdPhi->display(phi) ;
    m_lcdAlpha->display(m_Stt->getAlpha()) ;
    m_lcdBeta->display(m_Stt->getBeta()) ;
    m_lcdDelta->display(m_Stt->getDelta()) ;
    m_lcdTrans->display(m_Stt->getPhiAdim()) ;
    if (phi > 0) {
        m_surfaceFlow->setText(FLOWRT) ;
        m_deepFlow->setText(FLOWLT) ;
    } else {
        m_surfaceFlow->setText(FLOWLT) ;
        m_deepFlow->setText(FLOWRT) ;
    }
}
