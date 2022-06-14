#include "../../ft_irc.hpp"

/*===== channel existe pas =====*/

//<< JOIN #ijfe
//>> :tle!~tle@freenode-a99.759.j1faas.IP JOIN :#ijfe
//>> :*.freenode.net 353 tle = #ijfe :@tle
//>> :*.freenode.net 366 tle #ijfe :End of /NAMES list.
//<< MODE #ijfe
//>> :*.freenode.net 324 tle #ijfe :+nt
//--> chanquery mode
//<< WHO #ijfe
//>> :*.freenode.net 329 tle #ijfe :1655124803
//--> event 329
//>> :*.freenode.net 352 tle #ijfe ~tle freenode-a99.759.j1faas.IP *.freenode.net tle H@s :0 Truyen danh Le
//--> silent event who
//>> :*.freenode.net 315 tle #ijfe :End of /WHO list.
//--> chanquery who end
//<< MODE #ijfe b
//>> :*.freenode.net 368 tle #ijfe :End of channel ban list
//--> chanquery ban end

/*===== channel existe =====*/

//<< JOIN #test
//>> :*.freenode.net PONG *.freenode.net :*.freenode.net
//--> lag pong
//>> :tle!~tle@freenode-a99.759.j1faas.IP JOIN :#test
//>> :*.freenode.net 353 tle = #test :antoine Daniel071 saxo08451 sc0tt2 bogon darkphoenix tle Ali3000623883101
//>> :*.freenode.net 366 tle #test :End of /NAMES list.
//<< MODE #test
//>> :*.freenode.net 324 tle #test :+nt
//--> chanquery mode
//<< WHO #test
//>> :*.freenode.net 329 tle #test :1650500288
//--> event 329
//>> :*.freenode.net 352 tle #test ~antoine freenode-nda.1d0.9166ff.IP *.freenode.net antoine Hs :0 Antoine
//--> silent event who
//>> :*.freenode.net 352 tle #test ~Daniel071 freenode-fr2.5kn.e4r3kt.IP *.freenode.net Daniel071 Gs :0 Daniel
//--> silent event who
//>> :*.freenode.net 352 tle #test ~saxo08451 freenode-4ln.as1.b17r3t.IP *.freenode.net saxo08451 H :0 saxo
//--> silent event who
//>> :*.freenode.net 352 tle #test sid412351 freenode-gvelau.1gcv.uge0.8cnpra.IP *.freenode.net sc0tt2 Hs :0 Scott
//--> silent event who
//>> :*.freenode.net 352 tle #test ~bogon freenode-v17.qml.di46ae.IP *.freenode.net bogon Hs :0 ZNC - https://znc.in
//--> silent event who
//>> :*.freenode.net 352 tle #test darkphnx freenode-jo8546.7t3s.ckrk.8fsqam.IP *.freenode.net darkphoenix Hs :0 Jonas B
//--> silent event who
//>> :*.freenode.net 352 tle #test ~tle freenode-a99.759.j1faas.IP *.freenode.net tle Hs :0 Truyen danh Le
//--> silent event who
//>> :*.freenode.net 352 tle #test ~Ali3000 freenode-628.ult.j44gio.IP *.freenode.net Ali3000623883101 Hs :0 The Lounge User
//--> silent event who
//>> :*.freenode.net 315 tle #test :End of /WHO list.
//--> chanquery who end
//<< MODE #test b
//>> :*.freenode.net 368 tle #test :End of channel ban list
//--> chanquery ban end

void	join_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
		
}