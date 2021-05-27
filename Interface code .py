import socket 
import sys
import os
from tkinter import * 
from tkinter import ttk
from threading import Thread 
from datetime import datetime, date, time, timedelta
import calendar
from tkinter.messagebox import showinfo
from tkinter.messagebox import showerror
import sqlite3

ahora = datetime.now() 
fecha=date.today()
hoy=fecha.strftime("%d/%m/%Y")

host, port = "192.168.4.1", 80 
BUFSIZ = 1024 
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
client.connect((host, port)) 

data1=sys.argv[1:] 
data2=(sys.argv[2:])  
data3=(sys.argv[3:]) 
data4=(sys.argv[4:]) 
data5=(sys.argv[5:])
data6=(sys.argv[6:])
data7=(sys.argv[7:])
data8=(sys.argv[8:])
data9=(sys.argv[9:])
data10=(sys.argv[10:])

def lectura1(): 
		valor='2'+':'
		try:
			message = valor.encode() 
			print('sending {!r}'.format(message))
			client.send(message) 
			amount_received=0
			amount_expected=len(message)

			while   amount_received<amount_expected:

					data1=client.recv(BUFSIZ).decode() 
					data2=client.recv(BUFSIZ).decode()
					data3=client.recv(BUFSIZ).decode()
					data4=client.recv(BUFSIZ).decode()
					data5=client.recv(BUFSIZ).decode()
					
					amount_received += len(message)

					comp.insert(END,data1) 
					ciu.insert(END,data2)						
					ruc.insert(END,data3)					
					aut.insert(END,data4)
					prop.insert(END,data5)
											
					
		finally:
			pass

def lectura2(): 
		valor='3'+':'
		try:
			message = valor.encode() 
			print('sending {!r}'.format(message))
			client.send(message) 
			amount_received=0
			amount_expected=len(message)

			while   amount_received<amount_expected:

					data1=client.recv(BUFSIZ).decode() 
					data2=client.recv(BUFSIZ).decode()
					data3=client.recv(BUFSIZ).decode()
					data4=client.recv(BUFSIZ).decode()
					data5=client.recv(BUFSIZ).decode()
					data6=client.recv(BUFSIZ).decode()
					
					amount_received += len(message)

					ser.insert(END,data1) 
					k.insert(END,data2)						
					vcr.insert(END,data3)					
					vmax.insert(END,data4)
					pla.insert(END,data5)									
					nreg.insert(END,data6)
		finally:
			pass

def lectura3(): 
		valor='4'+':'
		try:
			message = valor.encode() 
			print('sending {!r}'.format(message))
			client.send(message) 
			amount_received=0
			amount_expected=len(message)

			while   amount_received<amount_expected:

					data1=client.recv(BUFSIZ).decode() 
					data2=client.recv(BUFSIZ).decode()
					data3=client.recv(BUFSIZ).decode()
					data4=client.recv(BUFSIZ).decode()
					data5=client.recv(BUFSIZ).decode()
					
					amount_received += len(message)

					master.insert(END,data1) 
					user1.insert(END,data2)						
					con1.insert(END,data3)					
					user2.insert(END,data4)
					con2.insert(END,data5)	
		finally:
			pass

def lectura4(): 
		valor='5'+':'
		try:
			message = valor.encode() 
			print('sending {!r}'.format(message))
			client.send(message) 
			amount_received=0
			amount_expected=len(message)

			while   amount_received<amount_expected:

					data1=client.recv(BUFSIZ).decode() 
					data2=client.recv(BUFSIZ).decode()
					data3=client.recv(BUFSIZ).decode()
					data4=client.recv(BUFSIZ).decode()
					data5=client.recv(BUFSIZ).decode()
					data6=client.recv(BUFSIZ).decode()
					data7=client.recv(BUFSIZ).decode()
					data8=client.recv(BUFSIZ).decode()
					data9=client.recv(BUFSIZ).decode()
					data10=client.recv(BUFSIZ).decode()

					amount_received += len(message)

					tm1.insert(END,data1) 
					ta1.insert(END,data2)						
					Vk1.insert(END,data3)					
					me1.insert(END,data4)
					ex1.insert(END,data5)									
					tm2.insert(END,data6) 
					ta2.insert(END,data7)						
					Vk2.insert(END,data8)					
					me2.insert(END,data9)
					ex2.insert(END,data10)
		finally:
			pass

def lectura5(): 
		valor='6'+':'
		try:
			message = valor.encode() 
			print('sending {!r}'.format(message))
			client.send(message) 
			amount_received=0
			amount_expected=len(message)

			while   amount_received<amount_expected:

					data1=client.recv(BUFSIZ).decode() 
					data2=client.recv(BUFSIZ).decode()
					data3=client.recv(BUFSIZ).decode()
					data4=client.recv(BUFSIZ).decode()
					
					amount_received += len(message)
					
					frevday.configure(state='normal')
					frevmonth.configure(state='normal')
					frevyear.configure(state='normal')
					furday.configure(state='normal')
					frevday.insert(END,data1)					
					frevmonth.insert(END,data2)
					frevyear.insert(END,data3)					
					furday.insert(END,data4)
					frevday.configure(state='disabled')
					frevmonth.configure(state='disabled')
					frevyear.configure(state='disabled')
					furday.configure(state='disabled')							
					
		finally:
			pass

def enviar1(): 
	valor='7'+':'+comp.get()+':'+ciu.get()+':'+ruc.get()+':'+aut.get()+':'+prop.get()
	try:		 
		dato=valor.encode() 
		client.send((dato))
		print('sending {!r}'.format(dato))
						
	finally:
		pass

def enviar2(): 
	valor='8'+':'+ser.get()+':'+k.get()+':'+vcr.get()+':'+vmax.get()+':'+pla.get()+':'+nreg.get()
	try:		 
		dato=valor.encode()
		client.send((dato))
		print('sending {!r}'.format(dato))
						
	finally:
		pass

def enviar3(): 
	valor='9'+':'+master.get()+':'+user1.get()+':'+con1.get()+':'+user2.get()+':'+con2.get()
	try:		 
		dato=valor.encode() 
		client.send((dato))
		print('sending {!r}'.format(dato))
						
	finally:
		pass

def enviar4(): 
	valor='10'+':'+tm1.get()+':'+ta1.get()+':'+Vk1.get()+':'+me1.get()+':'+ex1.get()+':'+tm2.get()+':'+ta2.get()+':'+Vk2.get()+':'+me2.get()+':'+ex2.get()
	try:		 
		dato=valor.encode()
		client.send((dato))
		print('sending {!r}'.format(dato))
						
	finally:
		pass

def enviar5(): 
	furday.configure(state='normal')
	furday.delete(0,END)
	furday.insert(END,hoy)
	furday.configure(state='disabled')
	valor='11'+':'+day.get()+':'+month.get()+':'+year.get()+':'+hora.get()+':'+minuto.get()+':'+segundo.get()+':'+frevday.get()+':'+frevmonth.get()+':'+frevyear.get()+':'+furday.get()
	try:		 
		dato=valor.encode()
		client.send((dato))
		print('sending {!r}'.format(dato))
						
	finally:
		pass

def click():
	frevday.config(state='normal')
	frevmonth.config(state='normal')
	frevyear.config(state='normal')

def click1():
	day.config(state='normal')
	month.config(state='normal')
	year.config(state='normal')
	hora.config(state='normal')
	minuto.config(state='normal')
	segundo.config(state='normal')

def borrar1():
	comp.delete(0,END)
	ciu.delete(0,END)
	ruc.delete(0,END)
	aut.delete(0,END)
	prop.delete(0,END)

def borrar2():
	ser.delete(0,END)
	k.delete(0,END)
	vcr.delete(0,END)
	vmax.delete(0,END)
	pla.delete(0,END)
	nreg.delete(0,END)

def borrar3():
	master.delete(0,END)
	user1.delete(0,END)
	con1.delete(0,END)
	user2.delete(0,END)
	con2.delete(0,END)

def borrar4():
	tm1.delete(0,END)
	ta1.delete(0,END)
	Vk1.delete(0,END)
	me1.delete(0,END)
	ex1.delete(0,END)
	tm2.delete(0,END)
	ta2.delete(0,END)
	Vk2.delete(0,END)
	me2.delete(0,END)
	ex2.delete(0,END)
	
	
def Salir():
	valor= '12'+':'
	try:		 
		dato=valor.encode()
		client.send((dato))
		print('sending {!r}'.format(dato))
	finally:
		ventana.quit() 
		client.close() 
def login():
	db = sqlite3.connect('/home/hector/Documentos/usuarios/login.db')
	c = db.cursor()	
	usuario = caja1.get()
	contr = caja2.get()	
	c.execute('SELECT * FROM usuarios WHERE usuario = ? AND pass = ?', (usuario, contr))
	
	if c.fetchall():
		showinfo(title = "Login correcto", message = "Usuario y contraseña correctos")
		abrirventana()		
		caja1.configure(state='disabled')
		caja2.configure(state='disabled')
		botonlogin.place_forget()
	else:
		showerror(title = "Login incorrecto", message = "Usuario o contraseña incorrecta")
		
	c.close()
	
def ventana1():
	
	ventana = Tk() 
	ventana.title("Interfaz de Usuario: Taximetro UTN") 
	ventana.geometry('270x150')
	Label(ventana, text = "Usuario:").pack()
	caja1 = Entry(ventana)
	caja1.pack()
	Label(ventana, text = "Contraseña:").pack()
	caja2 = Entry(ventana, show = "*")
	caja2.pack()
	botonlogin = Button (text = "Login", command = login)
	botonlogin.place(x=100, y=100)
	ventana.mainloop() 

def abrirventana():
		
	informacion1=Toplevel()
	informacion=ttk.Notebook(informacion1)	
	informacion.pack(fill='both',expand='yes')
	pes1=ttk.Frame(informacion)
	pes2=ttk.Frame(informacion)
	pes3=ttk.Frame(informacion)
	pes4=ttk.Frame(informacion)
	pes5=ttk.Frame(informacion)
	informacion.add(pes1,text='Información General')
	informacion.add(pes2,text='Parámetros')
	informacion.add(pes3,text='Usuarios')
	informacion.add(pes4,text='Tarifas')
	informacion.add(pes5,text='Servicio Técnico')


	info=Frame(pes1)
	info=LabelFrame(pes1, text="Información General",font=("Helvetica",12),padx=5, pady=5)
	info.grid(column=0,row=0,padx=(10,10),pady=(5,5),sticky=W)

	etiqueta = Label(info, text="Compañía:",font=("Helvetica",12))
	etiqueta.grid(column=0, row=0,sticky=W)
	comp = Entry(info,width=30,font=("Helvetica",8)) 
	comp.grid(column=1, row=0,sticky=W,pady=(3,3))

	etiqueta = Label(info, text="Ciudad:",font=("Helvetica",12))
	etiqueta.grid(column=0, row=1,sticky=W)
	ciu = Entry(info,width=30,font=("Helvetica",8))
	ciu.grid(column=1, row=1,sticky=W)

	etiqueta = Label(info, text="RUC:",font=("Helvetica",12))
	etiqueta.grid(column=0, row=2,sticky=W)
	ruc = Entry(info,width=30,font=("Helvetica",8) )
	ruc.grid(column=1, row=2,sticky=W)

	etiqueta = Label(info, text="Aut. SRI:",font=("Helvetica",12))
	etiqueta.grid(column=0, row=3,sticky=W)
	aut = Entry(info,width=30,font=("Helvetica",8)) 
	aut.grid(column=1, row=3,sticky=W)

	etiqueta = Label(info, text="Propietario:",font=("Helvetica",12))
	etiqueta.grid(column=0, row=4,sticky=W)
	prop = Entry(info,width=30,font=("Helvetica",8)) 
	prop.grid(column=1, row=4,sticky=W)

	info1=Frame(pes2)
	info1=LabelFrame(pes2, text="Parámetros",font=("Helvetica",12),padx=5, pady=5)
	info1.grid(column=0,row=0,padx=(10,10),pady=(5,5),sticky=NW,rowspan=2)

	etiqueta1 = Label(info1, text="Num. de Serie:",font=("Helvetica",12)) 
	etiqueta1.grid(column=0, row=0,sticky=W)
	ser = Entry(info1,width=20,font=("Helvetica",8)) 
	ser.grid(column=1, row=0,sticky=W)

	etiqueta1 = Label(info1, text="Constante K:",font=("Helvetica",12)) 
	etiqueta1.grid(column=0, row=1,sticky=W)
	k = Entry(info1,width=20,font=("Helvetica",8))  
	k.grid(column=1, row=1,sticky=W)

	etiqueta2 = Label(info1, text="Velocidad Crítica:",font=("Helvetica",12)) 
	etiqueta2.grid(column=0, row=2,sticky=W)
	vcr = Entry(info1,width=20,font=("Helvetica",8)) 
	vcr.grid(column=1, row=2,sticky=W)

	etiqueta2 = Label(info1, text="Velocidad Máxima:",font=("Helvetica",12)) 
	etiqueta2.grid(column=0, row=3,sticky=W)
	vmax = Entry(info1,width=20,font=("Helvetica",8)) 
	vmax.grid(column=1, row=3,sticky=W)

	etiqueta1 = Label(info1, text="Placa:",font=("Helvetica",12)) 
	etiqueta1.grid(column=0, row=4,sticky=W)
	pla = Entry(info1,width=20,font=("Helvetica",8))  
	pla.grid(column=1, row=4,sticky=W)

	etiqueta2 = Label(info1, text="Num.de registro:",font=("Helvetica",12)) 
	etiqueta2.grid(column=0, row=5,sticky=W)
	nreg = Entry(info1,width=20,font=("Helvetica",8))  
	nreg.grid(column=1, row=5,sticky=W)

	user=Frame(pes3)
	user=LabelFrame(pes3, text="Usuarios",font=("Helvetica",12),padx=5, pady=5)
	user.grid(column=0,row=0,padx=(10,0),pady=(5,5),sticky=NW)

	etiqueta1 = Label(user, text="Llave Master:",font=("Helvetica",12)) 
	etiqueta1.grid(column=0, row=0,sticky=W)
	master = Entry(user,width=20,font=("Helvetica",8))  
	master.grid(column=1, row=0,sticky=W)

	etiqueta1 = Label(user, text="Chofer 1:",font=("Helvetica",12)) 
	etiqueta1.grid(column=0, row=1,sticky=W)
	user1= Entry(user,width=20,font=("Helvetica",8))  
	user1.grid(column=1, row=1,sticky=W)

	etiqueta2 = Label(user, text="Contraseña 1:",font=("Helvetica",12)) 
	etiqueta2.grid(column=0, row=2,sticky=W)
	con1= Entry(user,width=20,font=("Helvetica",8)) 
	con1.grid(column=1, row=2,sticky=W)

	etiqueta2 = Label(user, text="Chofer 2:",font=("Helvetica",12)) 
	etiqueta2.grid(column=0, row=3,sticky=W)
	user2 = Entry(user,width=20,font=("Helvetica",8)) 
	user2.grid(column=1, row=3,sticky=W)

	etiqueta1 = Label(user, text="Contraseña 2:",font=("Helvetica",12)) 
	etiqueta1.grid(column=0, row=4,sticky=W)
	con2= Entry(user,width=20,font=("Helvetica",8)) 
	con2.grid(column=1, row=4,sticky=W)

	vp=Frame(pes4)
	vp=LabelFrame(pes4, text="Tarifas",font=("Helvetica"))
	vp.grid(column=0,row=0,sticky=NW,rowspan=4)


	tarifa=Frame(vp)
	tarifa=LabelFrame(vp, text="Tarifa Diurna",font=("Helvetica",12),padx=5, pady=5)
	tarifa.grid(column=0,row=0,padx=(10,10),pady=(5,5),sticky=NW)

	etiqueta = Label(tarifa, text="Tarifa mínima")
	etiqueta.grid(column=0, row=0,sticky=W)
	tm1 = Entry(tarifa,width=10) #cuadros de texto
	tm1.grid(column=1, row=0,sticky=W)

	etiqueta1 = Label(tarifa, text="Arranque") 
	etiqueta1.grid(column=0, row=1,sticky=W)
	ta1 = Entry(tarifa,width=10)
	ta1.grid(column=1, row=1,sticky=W)

	etiqueta2 = Label(tarifa, text="Valor por Km") 
	etiqueta2.grid(column=0, row=2,sticky=W)
	Vk1 = Entry(tarifa,width=10) 
	Vk1.grid(column=1, row=2,sticky=W)


	etiqueta3 = Label(tarifa, text="Minuto de espera") 
	etiqueta3.grid(column=0, row=3,sticky=W)
	me1 = Entry(tarifa,width=10) 
	me1.grid(column=1, row=3,sticky=W)

	etiqueta3 = Label(tarifa, text="Extras") 
	etiqueta3.grid(column=0, row=4,sticky=W)
	ex1 = Entry(tarifa,width=10) 
	ex1.grid(column=1, row=4,sticky=W)

	tarifa1=Frame(vp)
	tarifa1=LabelFrame(vp, text="Tarifa Nocturna y Feriados",font=("Helvetica",12),padx=5, pady=5)
	tarifa1.grid(column=1,row=0,padx=(10,10),pady=(5,5),sticky=SW)

	etiqueta = Label(tarifa1, text="Tarifa mínima")
	etiqueta.grid(column=0, row=0,sticky=W)
	tm2 = Entry(tarifa1,width=10) #cuadros de texto
	tm2.grid(column=1, row=0,sticky=W)

	etiqueta1 = Label(tarifa1, text="Arranque") 
	etiqueta1.grid(column=0, row=1,sticky=W)
	ta2 = Entry(tarifa1,width=10)
	ta2.grid(column=1, row=1,sticky=W)

	etiqueta2 = Label(tarifa1, text="Valor por Km") 
	etiqueta2.grid(column=0, row=2,sticky=W)
	Vk2 = Entry(tarifa1,width=10) 
	Vk2.grid(column=1, row=2,sticky=W)

	etiqueta3 = Label(tarifa1, text="Minuto de espera") 
	etiqueta3.grid(column=0, row=3,sticky=W)
	me2 = Entry(tarifa1,width=10) 
	me2.grid(column=1, row=3,sticky=W)

	etiqueta3 = Label(tarifa1, text="Extras") 
	etiqueta3.grid(column=0, row=4,sticky=W)
	ex2 = Entry(tarifa1,width=10)
	ex2.grid(column=1, row=4,sticky=W)

	va=Frame(pes5)
	va=LabelFrame(pes5, text="Fecha y Hora",font=("Helvetica",12),padx=5, pady=5)
	va.grid(column=0,row=0,padx=(10,10),pady=(5,5),sticky=NW)
	check1 = Checkbutton(va, text="Configuración Manual",command=click1)
	check1.grid(column=0, row=0,sticky=W,columnspan=4)

	etiqueta = Label(va, text="dd/MM/aaaa")
	etiqueta.grid(column=1, row=1,sticky=W)

	day = Entry(va,width=5,fg="black") 
	day.insert(END,ahora.day)
	day.configure(state='disabled') 
	day.grid(column=2, row=1,sticky=W)

	month = Entry(va,width=5)
	month.insert(END,ahora.month)
	month.configure(state='disabled') 
	month.grid(column=3, row=1,sticky=W)

	year = Entry(va,width=5) 
	year.insert(END,ahora.year)
	year.configure(state='disabled')
	year.grid(column=4, row=1,sticky=W)

	etiqueta = Label(va, text="H:mm:ss")
	etiqueta.grid(column=1, row=2,sticky=W)

	hora = Entry(va,width=5) 
	hora.insert(END,ahora.hour)
	hora.configure(state='disabled')
	hora.grid(column=2, row=2,sticky=W)

	minuto = Entry(va,width=5) 
	minuto.insert(END,ahora.minute)
	minuto.configure(state='disabled')
	minuto.grid(column=3, row=2,sticky=W)

	segundo = Entry(va,width=5) 
	segundo.insert(END,ahora.second)
	segundo.configure(state='disabled')
	segundo.grid(column=4, row=2,sticky=W)

	Frev=Frame(pes5)
	Frev=LabelFrame(pes5, text="Servicio Técnico",font=("Helvetica",12),padx=5, pady=5)
	Frev.grid(column=0,row=1,padx=(10,10),pady=(5,5),sticky=SW)

	check = Checkbutton(Frev, text="Fecha de próxima inspección", command=click)
	check.grid(column=0, row=0,sticky=W,columnspan=4)

	etiqueta = Label(Frev, text="dd/MM/aaaa")
	etiqueta.grid(column=0, row=1,sticky=W)

	frevday = Entry(Frev,width=5,state='disabled') 
	frevday.grid(column=1, row=1,sticky=W)

	frevmonth = Entry(Frev,width=5,state='disabled') 
	frevmonth.grid(column=2, row=1,sticky=W)

	frevyear = Entry(Frev,width=5,state='disabled') 
	frevyear.grid(column=3, row=1,sticky=W)

	etiqueta = Label(Frev, text="Última revisión técnica",font=("Helvetica",12), pady=5)
	etiqueta.grid(column=0, row=2,sticky=W,columnspan=4)
	etiqueta = Label(Frev, text="dd/MM/aaaa")
	etiqueta.grid(column=0, row=3,sticky=W)

	furday = Entry(Frev,width=10)
	furday.grid(column=1, row=3,sticky=W,columnspan=4)
	furday.configure(state='disabled')	

	botones=Frame(pes1)
	botones=LabelFrame(pes1, text="Comunicación",font=("Helvetica",12),padx=5, pady=5)
	botones.grid(column=0,row=2,padx=(10,10),pady=(10,10),rowspan=2)

	boton=Button(botones,text="Lectura",command=lectura1) #boton
	boton.grid(column=0,row=1,padx=(10,10),pady=(10,10))

	boton2=Button(botones,text="Enviar",command=enviar1)#boton
	boton2.grid(column=1,row=1,padx=(10,10),pady=(10,10))

	boton2=Button(botones,text="Borrar",command=borrar1)#boton
	boton2.grid(column=2,row=1,padx=(10,10),pady=(10,10))

	boton3=Button(botones,text="Salir",command=Salir,activebackground="lavender")#boton
	boton3.grid(column=3,row=1,padx=(10,10),pady=(10,10))

	botones=Frame(pes2)
	botones=LabelFrame(pes2, text="Comunicación",font=("Helvetica",12),padx=5, pady=5)
	botones.grid(column=0,row=2,padx=(10,10),pady=(10,10),rowspan=2)

	boton=Button(botones,text="Lectura",command=lectura2) #boton
	boton.grid(column=0,row=1,padx=(10,10),pady=(10,10))

	boton2=Button(botones,text="Enviar",command=enviar2)#boton
	boton2.grid(column=1,row=1,padx=(10,10),pady=(10,10))

	boton2=Button(botones,text="Borrar",command=borrar2)#boton
	boton2.grid(column=2,row=1,padx=(10,10),pady=(10,10))

	boton3=Button(botones,text="Salir",command=Salir)#boton
	boton3.grid(column=3,row=1,padx=(10,10),pady=(10,10))

	botones=Frame(pes3)
	botones=LabelFrame(pes3, text="Comunicación",font=("Helvetica",12),padx=5, pady=5)
	botones.grid(column=0,row=2,padx=(10,10),pady=(10,10),rowspan=2,sticky=NW)

	boton=Button(botones,text="Lectura",command=lectura3) #boton
	boton.grid(column=0,row=1,padx=(10,10),pady=(10,10))

	boton2=Button(botones,text="Enviar",command=enviar3)#boton
	boton2.grid(column=1,row=1,padx=(10,10),pady=(10,10))

	boton2=Button(botones,text="Borrar",command=borrar3)#boton
	boton2.grid(column=2,row=1,padx=(10,10),pady=(10,10))

	boton3=Button(botones,text="Salir",command=Salir)#boton
	boton3.grid(column=3,row=1,padx=(10,10),pady=(10,10))

	botones=Frame(pes4)
	botones=LabelFrame(pes4, text="Comunicación",font=("Helvetica",12),padx=5, pady=5)
	botones.grid(column=0,row=4,padx=(10,10),pady=(10,10),rowspan=2,sticky=NW)

	boton=Button(botones,text="Lectura",command=lectura4) #boton
	boton.grid(column=0,row=1,padx=(10,10),pady=(10,10))

	boton2=Button(botones,text="Enviar",command=enviar4)#boton
	boton2.grid(column=1,row=1,padx=(10,10),pady=(10,10))

	boton2=Button(botones,text="Borrar",command=borrar4)#boton
	boton2.grid(column=2,row=1,padx=(10,10),pady=(10,10))

	boton3=Button(botones,text="Salir",command=Salir)#boton
	boton3.grid(column=3,row=1,padx=(10,10),pady=(10,10))

	botones=Frame(pes5)
	botones=LabelFrame(pes5, text="Comunicación",font=("Helvetica",12),padx=5, pady=5)
	botones.grid(column=0,row=3,padx=(10,10),pady=(10,10),rowspan=2)

	boton=Button(botones,text="Lectura",command=lectura5) #boton
	boton.grid(column=0,row=1,padx=(10,10),pady=(10,10))

	boton2=Button(botones,text="Enviar",command=enviar5)#boton
	boton2.grid(column=1,row=1,padx=(10,10),pady=(10,10))


	boton3=Button(botones,text="Salir",command=Salir)#boton
	boton3.grid(column=3,row=1,padx=(10,10),pady=(10,10))
	informacion1.grab_set()

ventana1()
client.close()
