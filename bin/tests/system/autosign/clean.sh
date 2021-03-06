#!/bin/sh
#
# Copyright (C) 2009-2016  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

rm -f */K* */dsset-* */*.signed */trusted.conf */tmp* */*.jnl */*.bk
rm -f */core
rm -f */example.bk
rm -f */named.memstats
rm -f */named.run
rm -f activate-now-publish-1day.key
rm -f active.key inact.key del.key unpub.key standby.key rev.key
rm -f sync.key
rm -f delayksk.key delayzsk.key autoksk.key autozsk.key
rm -f dig.out.*
rm -f digcomp.out.test*
rm -f missingzsk.key inactivezsk.key
rm -f nopriv.key vanishing.key del1.key del2.key
rm -f ns*/named.lock
rm -f ns1/root.db
rm -f ns2/example.db
rm -f ns2/private.secure.example.db ns2/bar.db
rm -f ns3/*.nzf
rm -f ns3/autonsec3.example.db
rm -f ns3/sync.example.db
rm -f ns3/kg.out ns3/s.out ns3/st.out
rm -f ns3/nozsk.example.db ns3/inaczsk.example.db
rm -f ns3/nsec.example.db
rm -f ns3/nsec3-to-nsec.example.db
rm -f ns3/nsec3.example.db
rm -f ns3/nsec3.nsec3.example.db
rm -f ns3/nsec3.optout.example.db
rm -f ns3/oldsigs.example.db
rm -f ns3/optout.example.db
rm -f ns3/optout.nsec3.example.db
rm -f ns3/optout.optout.example.db
rm -f ns3/prepub.example.db
rm -f ns3/prepub.example.db.in
rm -f ns3/reconf.example.db
rm -f ns3/rsasha256.example.db ns3/rsasha512.example.db
rm -f ns3/secure-to-insecure.example.db
rm -f ns3/secure-to-insecure2.example.db
rm -f ns3/secure.example.db
rm -f ns3/secure.nsec3.example.db
rm -f ns3/secure.optout.example.db
rm -f ns3/ttl*.db
rm -f nsupdate.out
rm -f signing.out.*
rm -f settime.out.*
