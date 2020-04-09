package com.company.Angajati;

public class AngajatCuDepartament extends Angajat {
    private String departament;

    public AngajatCuDepartament(){
        super();
        this.typeAngajat = "AngajatCuDepartament";
        departament = null;
    }
    public AngajatCuDepartament(String nume, int salariu, String departament) {
        super(nume, salariu);
        this.typeAngajat = "AngajatCuDepartament";
        this.departament = departament;
    }

    public String getDepartament() {
        return departament;
    }

    public void setDepartament(String departament) {
        this.departament = departament;
    }

    @Override
    public void afisare(){
        System.out.println("nume: " + nume);
        System.out.println("salariu: " + salariu);
        System.out.println("departament: " + departament);
        System.out.println("ID angajat: " + idAngajat);
        System.out.println("Functia angajatului: " + typeAngajat);
        if(this.vacanta == true)
            System.out.println("ANGAJATUL SE AFLA IN VACANTA!");
    }
}
