function time_h()

{
	date=new Date;
	h=date.getHours();
	
	var el=document.getElementById("hr1")
	if(h!=12)
		h=h%12;
	
	el.style.backgroundImage = "url('img/sec_"+h*30+".jpg')";
	if(h>9)
		return (h);
	else
		return("0"+h)

}

function time_m()

{
	date=new Date;
	h=date.getMinutes();
	
	var el=document.getElementById("min1")
	
	el.style.backgroundImage = "url('img/sec_"+Math.floor(h/5)*30+".jpg')";
	if(h>9)
		return (h);
	else
		return("0"+h)

}

function time_s()

{
	date=new Date;
	h=date.getSeconds();
	
	var el=document.getElementById("sec1")
	
	el.style.backgroundImage = "url('img/sec_"+Math.floor(h/5)*30+".jpg')";
	
	if(h>9)
		return (h);
	else
		return("0"+h)

}

