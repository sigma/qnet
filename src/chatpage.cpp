/****************************************************************************
** Form implementation generated from reading ui file 'chatpage.ui'
**
** Created: Mon Jan 6 19:27:11 2003
**      by: The User Interface Compiler ($Id: chatpage.cpp,v 1.2 2003/02/15 20:53:06 Sigma Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "chatpage.h"

#include <qvariant.h>
#include <qlistbox.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <qsplitter.h>
#include <qvaluelist.h>

#include "mtpbrowser.h"
static const char* const image0_data[] = { 
"22 22 258 2",
"Qt c None",
".a c #292f13",
"bY c #313521",
"bO c #343727",
"c# c #363c20",
"bF c #37382f",
"bu c #383a31",
".V c #383b2a",
"#P c #393b31",
"## c #393c2e",
"b9 c #394020",
"#p c #3a3c32",
"c. c #3c4125",
".E c #404432",
".# c #40491e",
"bE c #464839",
"bt c #46483c",
"#O c #46493d",
"#C c #47493d",
"#o c #474a3d",
".m c #474b38",
"#. c #484a3e",
"b5 c #484c3c",
".U c #494c3f",
"#n c #515446",
".9 c #525547",
"bX c #525d27",
"bP c #535646",
".T c #535648",
"b8 c #535e26",
".D c #555849",
".8 c #575a4b",
"bs c #575c41",
"#w c #585b4c",
"al c #595c4b",
"#5 c #595d4b",
"#N c #595f40",
".S c #5b5e4f",
"bG c #5c5f4e",
"a# c #5d6248",
"#m c #5d6346",
"#x c #5e6349",
"a8 c #5f644a",
"ba c #5f6549",
"bZ c #5f6a30",
"b4 c #5f6c2f",
".b c #5f6d2c",
"bn c #606646",
".7 c #626949",
"ax c #636a45",
"b6 c #63702a",
".l c #646757",
"#H c #646c42",
".C c #66695b",
"aL c #666e48",
"bN c #667723",
"aU c #676e4c",
"aw c #676f45",
"a9 c #687048",
".R c #696d5c",
"aM c #697243",
"am c #69743e",
"bQ c #697635",
"aT c #6b734b",
"aa c #6c783c",
"aD c #6d754f",
"#v c #6d7a3a",
"bh c #6d7c30",
"#1 c #6f7f2f",
"#T c #707e37",
"b0 c #708326",
"a4 c #72822d",
"b3 c #738723",
"bT c #74852a",
".B c #75776b",
"bW c #758a1d",
"bx c #768634",
"bz c #768636",
"b7 c #768c1c",
"ak c #77863b",
"by c #788837",
"#X c #79873f",
"#B c #7a8c2e",
"#K c #7a8c30",
".A c #7b7d71",
".Q c #7b8845",
"#J c #7b8847",
"b# c #7b893f",
".z c #7c7e73",
"ar c #7d855e",
".G c #7f8276",
"#y c #7f9136",
"bH c #809529",
"bD c #81991b",
".k c #828479",
"bi c #828866",
".y c #83886b",
"ab c #839b20",
"af c #848a6a",
"bv c #859933",
"bo c #869740",
"bS c #86a01c",
".q c #888b80",
".c c #898c7e",
"#I c #89974d",
"#g c #89a223",
"bR c #89a41d",
"b2 c #89a517",
".j c #8a8d82",
"#h c #8aa323",
"aP c #8aa51a",
"b1 c #8aa617",
".n c #8b8e80",
".r c #8c8e80",
".x c #8c9566",
"#Y c #8ca521",
"bA c #8ca621",
"#f c #8ca720",
"bV c #8cab13",
".i c #8d8f85",
"#i c #8da529",
".h c #8e9086",
"#l c #8ea91d",
".g c #8f9187",
".6 c #8fa921",
"br c #8fac17",
"bM c #8faf0f",
"a2 c #90a925",
"bC c #90b011",
".f c #92948a",
".d c #939589",
"ae c #93af1d",
"#G c #93b119",
".F c #94968d",
"bb c #94aa39",
"#4 c #94b01c",
"bL c #94b30f",
"bU c #94b311",
"az c #94b313",
"#M c #94b316",
"#u c #94b318",
"ay c #95b319",
"ao c #95b512",
".p c #97998f",
"a7 c #97ac41",
"bK c #97b80f",
".H c #989b89",
"#U c #98a26d",
"aq c #98b328",
"bw c #98b817",
"bJ c #98b90f",
"bg c #98b910",
".s c #999d89",
"#q c #999d8b",
"#6 c #99a17a",
".P c #99b138",
"bB c #99ba0f",
"bI c #99bb0f",
".e c #9a9c93",
"bm c #9bb921",
"a3 c #9bbc0f",
"aO c #9bbd0f",
"#0 c #9cbe0f",
".W c #9da08c",
"bf c #9dbf10",
"an c #9dc011",
"#a c #9ea28e",
"#A c #9ec010",
"#Z c #9ec110",
"#S c #9ec112",
"a5 c #9faf5a",
"b. c #9fb838",
"#L c #9fc011",
"aN c #9fc210",
"#e c #a0c210",
"bq c #a0c310",
"#j c #a1bd31",
"#z c #a1c410",
".5 c #a1c411",
"aC c #a3b945",
"bj c #a4c229",
"aK c #a5c038",
"a1 c #a6c03d",
"aY c #a7c03c",
"#t c #a7c71e",
"bl c #a7c81f",
"bk c #a8c923",
"a. c #a9c829",
"bp c #aaca27",
".o c #abada5",
".w c #abbb65",
"av c #abc738",
"#k c #abca2a",
"#D c #acb294",
"be c #accb2d",
".1 c #adcb2e",
".4 c #adcc2f",
"bc c #afca42",
".2 c #afcd33",
"#d c #afcd34",
"aZ c #afcd35",
".O c #b0ca45",
"#F c #b0cd35",
"aJ c #b0cd36",
"aV c #b3c95b",
"aj c #b3cd45",
".3 c #b3d03f",
".0 c #b4d041",
"aS c #b5cc52",
"aI c #b6d144",
"bd c #b6d145",
"a0 c #b6d146",
".v c #b7c677",
"aX c #b7d14d",
"a6 c #b7d249",
"ad c #b8d24a",
"aQ c #b9cd65",
"#3 c #bad450",
".N c #bdd556",
"#9 c #bdd657",
"#W c #bdd658",
".t c #bfc79a",
".u c #bfcb8b",
"aA c #bfd274",
"aW c #c0d75f",
"au c #c0d860",
"aR c #c1d861",
"aH c #c1d862",
"aB c #c2d964",
".M c #c3d965",
".Z c #c4da6a",
".I c #c5cda9",
"#R c #c5db6c",
"#Q c #cad59a",
".L c #cadd77",
"ai c #cade79",
"ap c #cbde7b",
"aE c #cbde7d",
"#V c #ccdf7d",
"aG c #ccdf7f",
"#2 c #cddc8d",
"#s c #cde080",
"ac c #cee081",
"#c c #cee083",
"#8 c #d1e289",
"aF c #d2e38c",
"at c #d2e38d",
".K c #d4e492",
"as c #d5e2a2",
"#E c #d5e594",
"ag c #d7e0af",
".J c #d7e3a9",
".Y c #d7e69a",
"ah c #dce9a6",
"#7 c #dde9a8",
"#r c #e1eab8",
"#b c #e1ebb8",
".X c #e5eebf",
"QtQtQt.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.#QtQtQt",
"Qt.b.a.c.d.e.f.g.h.h.h.h.h.h.i.j.k.l.m.a.bQt",
"Qt.a.n.o.p.q.r.s.t.u.v.w.x.y.z.A.B.C.D.E.aQt",
".#.c.o.F.G.H.I.J.K.L.M.N.O.P.Q.R.C.S.T.U.V.#",
".a.d.p.G.W.X.Y.Z.0.1.2.3.3.4.5.6.7.8.9#.##.a",
".a.e.q#a#b#c#d#e#f#g#h#i#j#k.5#e#l#m#n#o#p.a",
".a.f#q#r#s#t#u#v#w#w#w#w#x#y#z#e#A#B#n#C#p.a",
".a.g#D#E#F#G#H#w#w#w#w#I#J#w#K#L#A#M#N#O#P.a",
".a.h#Q#R#S#T#w#w#w#w#U#V#W#X#w#Y#Z#0#1#O#P.a",
".a.h#2#3#4#5#w#w#w#6#7#8#9a.a#aa#Z#0ab#O#P.a",
".a.hacadae#w#w#wafagahaiajakalaman#0ao#O#P.a",
".a.hap#9aq#w#warasahatauavaw#waxay#0az#O#P.a",
".a.haAaBaC#waDaEaFaGaHaIaJaKaLaMaNaOaP#O#P.a",
".a.haQaRaSaTaUaVaWaXaYaZ.3a0a1a2#Za3a4#O#P.a",
".a.ia5a6a0a7a8a9b.b#babbbcbdbe#ebfbgbh#O#P.a",
".a.jbibjbkblbmbn#w#w#w#wbobpbq#Aa3brbsbtbu.a",
".a.k.Bbv#e#e#ebw#KbxbybzbAaNbfaObBbCbDbEbF.a",
".a.l.CbGbH#A#A#A#ZaN#Z#ZbfaObIbJbKbLbMbNbO.a",
".#.m.D.TbPbQbR#0#0#0aOa3bIbJbSbTbUbVbWbXbY.#",
"Qt.a.E.U#.#o#CbZb0b1b1b2b3b4b5btb6b7b8b9.aQt",
"Qt.b.a.V###p#p#P#P#P#P#P#P#P#PbubFc.c#.a.#Qt",
"QtQtQt.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.#QtQtQt"};


/* 
 *  Constructs a ChatPage as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ChatPage::ChatPage( QWidget* parent, const char* name, WFlags fl )
    : Master( parent, name, fl ),
      image0( (const char **) image0_data )
{
    if ( !name )
	setName( "ChatPage" );
    
    ChatPageLayout = new QGridLayout( this, 1, 1, 6, 6, "ChatPageLayout");
    
    QSplitter *vsplit = new QSplitter(Qt::Vertical,this);
    QSplitter *hsplit = new QSplitter(Qt::Horizontal,vsplit);
    
    chat_view = new MtpBrowser(hsplit,"chat_view");
    users_box = new QListBox(hsplit,"users_box");
    chat_edit = new QTextEdit(vsplit,"chat_edit");
    
    QValueList<int> list = vsplit->sizes();
    int tmp = list[1];
    list[1] = 0; // Strange things happend here...
    list[0] += tmp-list[1];
    vsplit->setSizes(list);
    
    list = hsplit->sizes();
    tmp = list[1];
    list[1] = 0; // Strange things happend here...
    list[0] += tmp-list[1];
    hsplit->setSizes(list);
    
    ChatPageLayout->addWidget(vsplit,0,0);
    /*
    ChatPageLayout = new QGridLayout( this, 1, 1, 6, 6, "ChatPageLayout"); 

    chat_edit = new QTextEdit( this, "chat_edit" );
    chat_edit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, chat_edit->sizePolicy().hasHeightForWidth() ) );
    chat_edit->setMaximumSize( QSize( 32767, 50 ) );
    chat_edit->setFrameShape( QTextEdit::LineEditPanel );

    ChatPageLayout->addMultiCellWidget( chat_edit, 1, 1, 0, 1 );

    users_box = new QListBox( this, "users_box" );
    users_box->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)7, 0, 0, users_box->sizePolicy().hasHeightForWidth() ) );
    users_box->setMaximumSize( QSize( 75, 32767 ) );

    ChatPageLayout->addWidget( users_box, 0, 1 );

    chat_view = new MtpBrowser( this, "chat_view" );

    ChatPageLayout->addWidget( chat_view, 0, 0 );
    languageChange();
    */
    resize( QSize(573, 361).expandedTo(minimumSizeHint()) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ChatPage::~ChatPage()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ChatPage::languageChange()
{
    setCaption( tr( "Form1" ) );
    QToolTip::add( chat_edit, tr( "SHIFT+UP/DOWN for history - CTRL+ENTER to insert a new line" ) );
}

void ChatPage::returnPressed()
{
    qWarning( "ChatPage::returnPressed(): Not implemented yet" );
}

