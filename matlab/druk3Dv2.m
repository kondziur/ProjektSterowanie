%fclose(s);
% close all; clear;
% x1 = 0;
% y1 = 1;
% z1 = 0;
% x2 = 0;
% y2 = 3;
% z2 = 0;
% x3 = 3 - ((2 * 3^0.5) / 2);
% y3 = 2;
% z3 = 0;
% xc = x3 / 2;
% yc = 2;
% zc = 2;
% r = 2;

close all; clear;
x1 = 2;
y1 = 0;
z1 = 0;
x2 = 8;
y2 = 0;
z2 = 0;
x3 = 5;
y3 = 3*sqrt(3);
z3 = 0;
xc = 5;
yc = sqrt(3);
zc = 0;
r = 7;



%x^2 + y^2 + z^2 = 1;

z1 = zc + sqrt(r^2 - (x1 - xc)^2 - (y1 - yc)^2);
z2 = zc + sqrt(r^2 - (x2 - xc)^2 - (y2 - yc)^2);
z3 = zc + sqrt(r^2 - (x3 - xc)^2 - (y3 - yc)^2);

col1 = line([x1 x1], [y1 y1], [0 10]);
col2 = line([x2 x2], [y2 y2], [0 10]);
col3 = line([x3 x3], [y3 y3], [0 10]);
arm1 = line([x1 xc], [y1 yc], [z1 zc]);
set(arm1, 'XData',[x1 xc],...
    'YData',[y1 yc],...
    'ZData',[z1 zc]);
arm2 = line([x2 xc], [y2 yc], [z2 zc]);
set(arm2, 'XData',[x2 xc],...
    'YData',[y2 yc],...
    'ZData',[z2 zc]);
arm3 = line([x3 xc], [y3 yc], [z3 zc]);
set(arm3, 'XData',[x3 xc],...
    'YData',[y3 yc],...
    'ZData',[z3 zc]);
view(-130, 36)

hold on
delete(instrfind);
s = serial('COM4');
set(s,'BaudRate',115200);
fopen(s);
pause(1)

fprintf(s,'init');
Koniec = 0;
while Koniec == 0%TUTAJ JEST B£¥D
    Lancuch = fread(s,1);
    if Lancuch == 107
        Koniec = 1;
    end
end

for t=0:0.05:20
    xc1 = xc + 6 * (0.1*sin(t));
    yc1 = yc + 6 * (0.1*cos(t));
    zc = 2;
    z1 = zc + sqrt(r^2 - (x1 - xc1)^2 - (y1 - yc1)^2);
    z2 = zc + sqrt(r^2 - (x2 - xc1)^2 - (y2 - yc1)^2);
    z3 = zc + sqrt(r^2 - (x3 - xc1)^2 - (y3 - yc1)^2);
    set(arm1, 'XData',[x1 xc1],...
        'YData',[y1 yc1],...
        'ZData',[z1 zc]);
    set(arm2, 'XData',[x2 xc1],...
        'YData',[y2 yc1],...
        'ZData',[z2 zc]);
    set(arm3, 'XData',[x3 xc1],...
        'YData',[y3 yc1],...
        'ZData',[z3 zc]);
    
    if exist('z01', 'var')
        kroki1 = z1 - z01;
        kroki2 = z2 - z02;
        kroki3 = z3 - z03;
    end
    
    plot3(xc1, yc1, zc, '.')
    
    z01 = z1;
    z02 = z2;
    z03 = z3;
    
    if exist('kroki1', 'var')
        tekst = ['x ' num2str(round(kroki1*1000))...
            ' y ' num2str(round(kroki2*1000))...
            ' z ' num2str(round(kroki3*1000))];
        fprintf(s, tekst);
        while s.BytesAvailable==0
        end
        a = fscanf(s,'%s');
    end
    drawnow();
end

fclose(s);