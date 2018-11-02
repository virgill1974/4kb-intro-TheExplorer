
static char Intro[] = \
"uniform vec3 t;"
"uniform sampler2D texData1;"
"float v=t.x;"
"vec2 m=vec2(t.y,t.z);"

"int f=0,z,i;"
//"float s[37]=float[37](2.3, 2.3,0.0,0.0,6.9,4.6,2.3  ,0.0,3.0,0.0,4.0,7.5,3.4,  8.0,8.5,5.0,5.0,5.0,5.0,  0.0,8.5,5.0,5.0,8.0,8.5  ,8.5,8.5,4.2,5.0,5.0,3.0,  6.9,8.0,2.0,2.5,3.6,4.6);"
//"float n[37]=float[37](0.0, 0.0,2.3,0.0,0.0,2.3,0.0  ,2.0,1.0,1.0,3.0,0.0,0.5,  0.0,0.0,3.0,3.0,4.0,3.0,  0.8,1.0,5.0,3.5,0.0,1.0  ,8.0,7.5,1.5,3.5,3.0,0.0,  0.0,0.3,0.0,0.0,0.0,0.0),y=4.,x=24.;"
"float s[37]=float[37](2.3,2.3,0,0,6.9,4.6,2.3,0,3,0,4,7.5,3.4,8,8.5,5,5,5,5,0,8.5,5,5,8,8.5,8.5,8.5,4.2,5,4,4.3,6.9,8,2,2.5,3.6,4.6),n[37]=float[37](0,0,2.3,0,0,2.3,0,2,1,1,3,0,0,0,0,3,3,4,3,.8,1,5,3.5,0,1,8,7.5,1.5,3.5,1.5,2.5,0,0,0,0,0,0),y=4.,x=24.;"


"vec2 r,l,e;"
"vec3 c,d=vec3(0,0,1);"
"float a,w;"

// noise
"float h(vec2 v)"
"{"
"return fract(sin(dot(v.xy,vec2(12.98,78.23)))*43758.5);"
"}"

// box sdf
"float h(vec3 v,vec3 z)"
"{"
"vec3 f=abs(v)-z;"
"return min(max(f.x,max(f.y,f.z)),0.)+length(max(f,0.));"
"}"
// 3d noise function (shane)
"float p(vec3 v)"
"{"
"vec3 f=floor(v);"
"v-=f;"
"vec3 z=vec3(7,157,113);"
"vec4 i=vec4(0.,z.yz,z.y+z.z)+dot(f,z);"
"v=v*v*(3.-2.*v);"
"i=mix(fract(sin(i)*43758.5),fract(sin(i+z.x)*43758.5),v.x);"
"i.xy=mix(i.xz,i.yw,v.y);"
"return mix(i.x,i.y,v.z);"
"}"
// cone sdf
"float p(vec3 v,vec2 f)"
"{"
"return dot(f,vec2(length(v.xy),v.z));"
"}"
// rotation
"void g(inout vec2 v,float f)"
"{"
"v=cos(f)*v+sin(f)*vec2(v.y,-v.x);"
"}"
// fractal
"const float o=.6,u=1.;"
"float g(vec3 v)"
"{"
"v.x=mod(v.x+1.,2.)-1.;"
"vec4 f=vec4(v,1.),i=f;"
"for(int z=0;z<10;z++)"
"{"
"g(f.yz,1.55);"
"f.xyz=clamp(f.xyz,-u,u)*2.-f.xyz;"
"float y=dot(f.xyz,f.xyz);"
"f*=clamp(max(o/y,.6),0.,1.);"
"f=3./o*f-i;"
"}"
"return length(f.xyz)/f.w-.005;"
"}"

// map
"float D(vec3 i,int z)"
"{"
"float y=1.;"
"vec3 m=i;"
// sphere ship
"float d=length(m-c)-.1;"
// cone light
"vec3 x=m-c;"
"g(x.zx,-e.y);"
"g(x.yz,e.x);"
"float l=p(x,normalize(vec2(1,1)))/length(x*x)+.2*p(10.*i+2.*sin(.2*v))+.1*p(i*23.+sin(.3*v))+.2*h(i.xy);"
"a+=max(-l,0.)*.07;"
// falling objects
"if(f==1)"
"{"
"vec3 s=vec3(1.5);"
"i.y+=.4*v;"
"vec3 r=mod(i,s)-.5*s;"
"y=max(length(r)-.1,i.z-3.);"
"y-=.2*p(6.*i)+.005*p(80.*i);"
"y=min(y,i.z+4.);"
"}"
// wobble floor
"if(f==2)"
"y=i.y-.01*p(50.*i)+.4*p(2.*i+.2*v)+.09*p(7.*i);"
// room with stone
"if(f==3)"
"y=i.y-log(pow(length(i.xz),1.)+.2),y=min(y,length(i)-.4-.04*p(i*70.)-.5*p(i*4.+v)-.02*p(i*114.+v)),y+=.05*p(i*10.)-.009*p(i*-40.)+p(i*2.);"
// kleinian fractal
"if(f==4)"
"{"
"vec4 s=vec4(i,1.);"
"s*=.5;"
"s.x+=.5;"
"s.z+=1.;"
"for(int r=0;r<8;r++)"
"s.xyz=-1.+2.*fract(.5+.5*s.xyz),s=1.3*s/max(dot(s.xyz,s.xyz),.1);"
"y=max(.9*abs(s.y)/s.w,length(i)-3.5)-.002*p(50.*i);"
"w=1.-1./s.w;"
"}"
// wtf scene
"if(f==5)"
"i.z+=3.5,i.y-=.1*(v-120.),i.z-=.1*(v-120.),y=.5*g(i);"
"return min(d,y);"
"}"
// normal calculation
"vec3 D(vec3 v)"
"{"
"float i=.002,y=D(v,0);"
"if(f==4)"
"i=.2;"
"if(f==5)"
"i=.02;"
"return normalize(vec3(D(v+vec3(i,0,0),0)-y,D(v+vec3(0,i,0),0)-y,D(v+vec3(0,0,i),0)-y));"
"}"
// ray marching loop
"float D(in vec3 f,in vec3 z,in float y,in vec2 i)"
"{"
"float m=.001,s=m*2.,r=-3.5+h(i+.01*v)*7.;"
"for(int x=0;x<200;x++)"
"{"
"if(abs(s)<m||r>y)"
"continue;"
"s=D(f+z*r,1);"
"r+=.25*s;"
"}"
"return r;"
"}"

////////////////////////////////////////////////////
"void main()"
"{"
// scene handling
"i=int(floor((v+.8)/y));"
"f=int(floor(v/x));"
"r=vec2(s[i+1],n[i+1]);"
"l=vec2(s[i],n[i]);"
"e=mix(r,l,exp(-64.*pow(fract((v+.8)/y),4.)))*.7;"
// cam setuo
"vec2 z=gl_FragCoord/m.xy,u=z*2.-1.;"
"u.x*=m.x/m.y;"
"float o=v*3.14159*.2,h=5.*cos(o*.5),b=5.*sin(o*.5);"
"vec3 F=vec3(.5*h,4.,5.3);"
"if(f==5||f==0)"
"F=vec3(0.,8.,-.0001);"
//more cam
"vec3 C=vec3(0.,.25,0.),Z=normalize(C-F),Y=vec3(0.,1.,0.),X=normalize(cross(Z,Y)),W=normalize(cross(X,Z)),V=normalize(u.x*X+u.y*W+7.5*Z);"
"float U=.8;"
"if(f==1||f==3||f==5)"
"U=0.;"
"c=vec3(U,.7+.2*sin(o*2.),1.-.2*sin(.2*v));"
"if(f==5||f==0)"
"c=vec3(0,2,0);"
"g(d.yz,-e.x);"
"g(d.zx,e.y);"
// feedback noise
"z.x-=.005*p(z.yxx*32.-v)-.0025;"
"z.y+=.005*p(z.yxx*32.+v)-.0025;"
"vec3 T=texture2D(texData1,z).xyz,S=vec3(0);"
// render
"float R=D(F,V,15.,z),Q=clamp(R/5.-1.3,0.,1.);"
"if(R>15.)"
"R=-1e+06;"
// colors
"vec3 P=F+V*R,O=D(P),N=vec3(2.,.25,.0625);"
"if(f==3||f==5)"
"N=vec3(.0625, .25, 2.);"
// treat light as conelight
"float M=0.,L=1.;"
"vec3 K=normalize(c-P);"
"float J=dot(O,K),I=dot(d,normalize(K)),H=.7071,G=J,E=pow(clamp(dot(O,normalize(K+normalize(F-P))),0.,1.),60.);"
"if(J>0.&&I>H)"
"L=pow((I-H)/(1.-H),4.),M=(G+E)*L,S+=clamp(w,0.,1.)*a*L*vec3(.2,.05,0.);"
// particles
"float B;"
"for(int A;A<36;A++)"
"{"
"float q=float(A);"
"vec2 k=vec2(.5+.2*sin(q+.5*v+cos(.01*v*q))+.2*sin(-q),.5+.2*cos(q+.2*v+sin(.02*v*q)))+.2*cos(q);"
"B+=clamp(1.-length(350.*(.8+.5*sin(q*v))*(k-z)),0.,1.);"
"}"
"if(f==2||f==3||f==4)"
"S+=B*M*(N+vec3(0,.5,0))*2.;"
// color for light + feedback
"S+=.3*a*vec3(1.,.8,.6)+.7*T;"
// color for material
"S+=.3*N*exp(6.*(-1.+M));"
// fade
"float q=min(3.*abs(sin(3.1415*v/x)),1.);"
// out
"gl_FragColor=vec4(S*q,Q);"
"}";




static char Intro2[] = \
"uniform vec3 t;"
"uniform sampler2D texData2;"
"float v=t.x;"
"vec2 r=vec2(t.y,t.z);"
"const float s=2.399;"
"mat2 m=mat2(cos(s),sin(s),-sin(s),cos(s));"
"vec3 n(sampler2D s,vec2 v,float f)"
"{"
"vec3 y=vec3(0);"
"vec2 n=vec2(.002*r.y/r.x,.002),c=vec2(0,f);"
"f=1.;"
"for(int u=0;u<80;u++)"
"{"
"f+=1./f;"
"c*=m;"
"vec4 g=texture2D(s,v+n*(f-1.)*c);"
"if(t.x>48.){"
"if(g.x>.999)g.x=4.;"
"if(g.y>.999)g.y=4.;"
"if(g.z>.999)g.z=4.;"
"}"
"y+=g.xyz;"
"}"
"return y/80.;"
"}"
"void main()"
"{"
"vec2 s=gl_FragCoord.xy/r.xy;"
"gl_FragColor=vec4(n(texData2,s,texture2D(texData2,s).w),1.);"
"}";