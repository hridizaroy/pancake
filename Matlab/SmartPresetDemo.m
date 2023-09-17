close all;
clear;

brightness = 0; %Linear Brightness Control
gain = 1;       %A Scalar exposure increase(Experimental)
% contrast = 1;   %A Scalar Contrast control(Experimental)
color = 0;      %Color Control
warmth = 0;     %Temperature Control
% saturation = 1;

a0 = imread("lenna_color.tif");
b0 = imread("harbor.tif");

%Map Size
ra = size(a0, 1);
ca = size(a0,2);
rb = size(b0, 1);
cb = size(b0,2);


a1 = rgb2hsv(a0); %Convert RGB to HSV(Hue, Saturation, Value)

%Offset the Distribution of Pixel Values for edit
a1(:,:,3) = (a1(:,:,3) * gain) + (ones(ra, ca, "double") * brightness/255); 
a1(:,:,2) = (a1(:,:,2)) + (ones(ra, ca, "double") * color/255);

% a1(:,:,2) = (a1(:,:,2)*saturation) + (ones(ra, ca, "double") - saturation);

%EXPERIMENTAL Contrast not functional
% a1VC = mean(a1(:,:,3), "all");
% a1(:,:,3) = a1(:,:,3) - a1VC;
% stda1 = std(a1(:,:,3), 0, "all");
% tgtStda1 = std(a1(:,:,3), 0, "all")*contrast;
% a1(:,:,3) = a1(:,:,3) * (contrast) + a1VC;

%Vectors Values for A1
a1VB = mean(a1(:,:,3), "all")*255;
a1VS = mean(a1(:,:,2), "all")*255;

%Convert A1 to an RGB for Display
a1 = hsv2rgb(a1);
a1 = uint8(a1*255);


b1 = rgb2hsv(b0);

%Find Vectors of b0
b0VB = mean(b1(:,:,3), "all")*255;
b0VS = mean(b1(:,:,2), "all")*255;

%Shift the Vectors to form image b1
b1(:,:,3) = b1(:,:,3) + (ones(rb, cb, "double") * (a1VB/255 - b0VB/255));
b1(:,:,2) = b1(:,:,2) + (ones(rb, cb, "double") * (a1VS/255 - b0VS/255));

%EXPERIMENTAL Contrast not functional
% b1VC = mean(b1(:,:,3), "all");
% b1(:,:,3) = b1(:,:,3) - b1VC;
% stdb1 = std(b1(:,:,3), 0, "all");
% b1(:,:,3) = b1(:,:,3) * (tgtStda1/stdb1) + b1VC;

%b1 Vector should match a1
b1VB = mean(b1(:,:,3), "all")*255;
b1VS = mean(b1(:,:,2), "all")*255;

%Convert to RGB
b1 = hsv2rgb(b1);
b1 = uint8(b1*255);
% b(:,:,2) = a1(:,:,2) * 255;

%Display Images
fig1 = figure;
imshow(a0)

fig2 = figure;
imshow(a1);

fig3 = figure;
imshow(b0)

fig4 = figure;
imshow(b1);





% mitu = [0.4306, 0.3415, 0.1784;
%         0.2220, 0.7067, 0.0713;
%         0.0202, 0.1295, 0.9394];
% mituNorm = [0.5141, 0.3239, 0.1604;
%             0.2651, 0.6702, 0.0641;
%             0.0241, 0.1228, 0.8444];
% xyz2lms = [0.3897 0.6890 -0.0787;
%            -0.2298 1.1834 0.0464;
%            0.0000 0.0000 1.0000];
% pca = diag([1/sqrt(3), 1/sqrt(6), 1/sqrt(2)]) * [1, 1, 1; 1, 1, -2; 1, -1, 0];
% pcaInv = [1, 1, 1; 1, 1, -1; 1, -2, 0] * diag([sqrt(3)/3, sqrt(6)/6, sqrt(2)/2]);
% 
% lms2rgb = [4.4679 -3.5873 0.1193
%           -1.2186 2.3809 -0.1624
%            0.0497 -0.2439 1.2045];
% 
% xyzSrc = double(src);
% lmsSrc = double(src);
% logSrc = double(src);
% labSrc = double(src);
% 
% xyztgt = double(tgt);
% lmstgt = double(tgt);
% logtgt = double(tgt);
% labtgt = double(tgt);
% 
% for c = 1:size(src, 2)
%     for r = 1:size(src, 1)
%         pixel = reshape(src(r, c, :), [3, 1]);
%         xyzSrc(r, c, :) = mituNorm * double(pixel);
%         pixel = reshape(xyzSrc(r, c, :), [3, 1]);
%         lmsSrc(r, c, :) = xyz2lms * double(pixel);
%         pixel = reshape(lmsSrc(r, c, :), [3, 1]);
%         for i = 1:3
%             if pixel(i) ~= 0
%                 pixel(i) = log10(double(pixel(i)));
%             end
%         end
%         logSrc(r, c, :) = double(pixel);
%         pixel = reshape(logSrc(r, c, :), [3, 1]);
%         labSrc(r, c, :) = pca * double(pixel);
%     end
% end
% for c = 1:size(a1, 2)
%     for r = 1:size(a1, 1)
%         pixel = reshape(labSrc(r, c, :), [3, 1]);
%         logSrc(r, c, :) = pcaInv * double(pixel);
%         lmsSrc(r,c,:) = 10.^logSrc(r,c,:);
%         pixel = reshape(lmsSrc(r, c, :), [3, 1]);
%         dst(r, c, :) = lms2rgb * double(pixel);
%     end
% end