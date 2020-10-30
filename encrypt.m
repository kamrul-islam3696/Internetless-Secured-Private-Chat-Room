function [enc] = encrypt1( msg,n )
e=3;

msg=msg-31;
enc=mod((msg.^e),n);
enc=strcat(enc,'#');
end

