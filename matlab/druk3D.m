x1 = 0;
y1 = 1;
z1 = 0;
x2 = 0;
y2 = 3;
z2 = 0;
x3 = 1;
y3 = 2;
z3 = 0;
xc = 0.3;
yc = 2.5;
zc = 2;
r = 2;
% Wysokosc kolumn
h = 3;

z1 = zc + sqrt(r^2

col1 = line([x1 x1], [y1 y1], [0 h])
col2 = line([x2 x2], [y2 y2], [0 h]);
col3 = line([x3 x3], [y3 y3], [0 h]);

arm1 = line([x1 xc],[y1 yc],[z1,zc]);
arm2 = line([x2 xc],[y2 yc],[z2,zc]);
arm3 = line([x3 xc],[y3 yc],[z3,zc]);

get(arm1)

for t=0:0.1:20
    xc = xc + 0.1 * sin(t);
    yc = yc + 0.1 * cos(t);
    zc = 2;
    z1=
    z2=
    z3=
    if exist('z01','var')
        kroki1=z1-z01;
    end
    if exist('z02','var')
        kroki2=z2-z02;
    end
    if exist('z03','var')
        kroki3=z3-z03;
    end
    
    set(arm1,'XData',[x1 xc],'YData',[y1 yc],'zdata',[z1 zc])
    set(arm2,'XData',[x2 xc],'YData',[y2 yc],'zdata',[z2 zc])
    set(arm3,'XData',[x3 xc],'YData',[y3 yc],'zdata',[z3 zc])
    plot3(xc,yc,zc,'.')
    z01=z1;
    z02=z2;
    z03=z3;
    tekst = ['x ' num2str(round(kroki1*10000))...
        ' y ' num2str(round(kroki2*10000))...
        ' z ' num2str(round(kroki3*10000)) '\n']
    pause(0.1)
end