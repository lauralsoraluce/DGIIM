#!/bin/sh
cd ../bin
if [ "v$HEADLESS" = "v" ]; then
    HEADLESS=false
fi

JAVA="../jre/bin/java"
if [ ! -f "$JAVA" ]; then
    JAVA="../../jre/bin/java"
fi

if [ ! -f "$JAVA" ]; then
    JAVA="../../jre.bundle/Contents/Home/jre/bin/java"
fi

if [ ! -f "$JAVA" ]; then
    JAVA="../../.install4j/jre.bundle/Contents/Home/jre/bin/java"
fi

if [ ! -f "$JAVA" ]; then
    JAVA="java"
fi

"$JAVA" -Xms256m -Xmx768m -XX:MaxPermSize=256m -Djava.awt.headless=$HEADLESS -cp ".:../lib/vpplatform.jar:../lib/jniwrap.jar:../lib/winpack.jar:../ormlib/orm.jar:../ormlib/orm-core.jar:../lib/lib01.jar:../lib/lib02.jar:../lib/lib03.jar:../lib/lib04.jar:../lib/lib05.jar:../lib/lib06.jar:../lib/lib07.jar:../lib/lib08.jar:../lib/lib09.jar:../lib/lib10.jar:../lib/lib11.jar:../lib/lib12.jar:../lib/lib13.jar:../lib/lib14.jar:../lib/lib15.jar:../lib/lib16.jar:../lib/lib17.jar:../lib/lib18.jar:../lib/lib19.jar:../lib/lib20.jar" com.vp.cmd.InstantGenerator "$@"
