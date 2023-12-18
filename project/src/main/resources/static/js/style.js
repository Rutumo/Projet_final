//Mise en forme du menu actif
var ul = document.querySelector('.group_btn');
var li = ul.children;
for(var i=0; i<li.length; i++){
	var a = li[i].lastElementChild;
	if(window.location == a.href){
		a.classList.add('href_active');
	}
}

/*
//Mise en forme lorsqu'on survole sur l'utilisateur
var user = document.querySelector('#user');
var aff = document.querySelector('#i_user');
user.addEventListener('click', function(){
	if(!aff.classList.contains('visible')){
		aff.classList.add('visible');
	}else if(aff.classList.contains('visible')){
		aff.classList.remove('visible');
	}
});
*/

//Mise en forme lorsqu'on click sur l'utilisateur
function portion(id){
	var aff = document.getElementById(id);
	if(!aff.classList.contains('visible')){
		aff.classList.add('visible');
	}else if(aff.classList.contains('visible')){
		aff.classList.remove('visible');
	}
}

/*
user.addEventListener('mouseover', function(){
	aff.classList.add('visible');
});
*/

//Mise en forme lorsqu'on click sur le bouton du menu
var menu = document.querySelector('#lien');
var btn_menu = document.querySelector('#btn_menu').lastElementChild;
var body = document.querySelector('#body');

btn_menu.addEventListener('click', function(){
	if(!menu.classList.contains('visible_m')){
		menu.classList.add('visible_m');
		var position = menu.getBoundingClientRect().bottom;
		body.style.marginTop = (position)+'px';
	}else if(menu.classList.contains('visible_m')){
		menu.classList.remove('visible_m');
		body.style.marginTop = 80+'px';
	}
});

//Mise en forme lorsqu'on click sur un des boutons + de l'acceil
var list = document.querySelectorAll('#A0');
for(var x=0; x<list.length; x++){
	var info = list[x].children;
	for(var i=0; i<info.length; i++){
		var ele = info[i].lastElementChild.children;
		for(var j=0; j<ele.length; j++){
			var btn_n2 = ele[j].firstElementChild;
			btn_n2.addEventListener('click', function(){
				var contenu1 = this.nextElementSibling.nextElementSibling;
				if(!contenu1.classList.contains('visible')){
					this.firstElementChild.classList.add('invisible');
					this.lastElementChild.classList.add('visible');
					contenu1.classList.add('visible');
				}else if(contenu1.classList.contains('visible')){
					contenu1.classList.remove('visible');
					this.firstElementChild.classList.remove('invisible');
					this.lastElementChild.classList.remove('visible');
				}
			});
		}
	}
}

//Mise en forme lorsqu'on survole un post
var i_accueil = document.querySelectorAll('.i_accueil');
for(var x=0; x<i_accueil.length; x++){
	i_accueil[x].addEventListener('mouseover', function(){
		this.firstElementChild.nextElementSibling.classList.add('visible');
	});
	i_accueil[x].addEventListener('mouseout', function(){
		this.firstElementChild.nextElementSibling.classList.remove('visible');
	});
}

//Lors qu'on click sur le bouton imprimer
function imprimer(id){
	var imprimer = document.getElementById(id).innerHTML
	var page = document.body.innerHTML;
	document.body.innerHTML = imprimer;
	window.print();
	document.body.innerHTML = page;
}


//function imprimer(id){
//	var imprimer = document.getElementById(id);
//	var page = window.open('/oeilsurvous/', '_blank');
//	page.document.open();
//	page.document.write('<html><body onload="window.print()">'+ imprimer.innerHTML +'</html>');
//	page.document.close();
//}

//Mise en forme lorsqu'on click sur sup
// var sup = document.querySelector('#sup');
// window.addEventListener('scroll', function(){
	// var scrolly = window.scrollY;
	// var fix = sup.classList.contains('visible');
	// if(scrolly > 1000 && !fix){
		// sup.classList.add('visible');
	// }else if(scrolly < 1000 && fix){
		// sup.classList.remove('visible');
	// }
// });
// sup.addEventListener('click', function(){
	// var p_body = body.getBoundingClientRect().top;
	// var p_menu = menu.getBoundingClientRect().bottom;
	// alert(p_menu);
	// body.style.marginTop = p_menu+'px';
// });
