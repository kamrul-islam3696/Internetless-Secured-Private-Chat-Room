function [dcp] = decrypt1( enc,d,n )
enc=double(enc);
for i=1:length(enc)
    x=num2str(enc(i));
    x=sym(x);
    dcp(i)=x.^d;
    dcp(i)=mod(dcp(i),n);
    dcp(i)=dcp(i)+31;
end
    dcp=char(double(dcp));
end

