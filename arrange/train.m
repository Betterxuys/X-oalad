%��ȡԭ���ݣ�����ѹ��Ϊ3*5 ԭ���������淶left1.bmp
data=[];
for i=1:119
s=sprintf('%s%d%s','left',i,'.bmp');
p=imread(s);
%p=rgb2gray(p);
%p=histeq(p);
%p=imresize(p,[3,5]);
%��ȡ3*5ͼƬ����������ݼ�data m*15 
p=reshape(p,1,15);
data=[data;p];
end

label=[];
%load label
for i=0:118
s=sprintf('%d%s',i,'.txt');
p=load(s);
label=[label;p];
end
newlabel=[];
%����label
for i=1:119
newlabel=[newlabel;floor(label(i,2)/320)*4+floor(label(i,1)/480)];
end
data=double(data);
newlabel=double(newlabel);

%ѵ��������
net.trainparam.max_fail=20;
net=cascadeforwardnet([4,1],'traingdx');
net.trainparam.lr=0.2;
net.trainparam.epochs=1000;
net.trainparam.max_fail=20;
net.init();
net.layers{1}.transferfcn='logsig';
net.layers{2}.transferfcn='logsig';
net=train(net,data',newlabel');

