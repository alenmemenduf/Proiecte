package com.company.Angajati;
import java.util.*;
import java.time.*;

public final class Service {
    private ArrayList<Angajat> Angajati;
    private HashMap<String, Integer> frecventaAngajati = new HashMap<>();
    private Vector<String> ierarhieAngajati = new Vector<>();

    public Service(){
        CsvRepo csvRepo = CsvRepo.getInstance();

        Angajati = new ArrayList<>();
        try {
            Angajati.addAll(csvRepo.read("./Angajati.csv", Angajat.class));
            Angajati.addAll(csvRepo.read("./DirectoriDeCanal.csv", DirectorDeCanal.class));
            Angajati.addAll(csvRepo.read("./MembriDeProiect.csv", MembruDeProiect.class));
            Angajati.addAll(csvRepo.read("./DirectoriDeDepartament.csv", DirectorDeDepartament.class));
        } catch (Exception e) {
            e.printStackTrace();
        }

        ierarhieAngajati.add("Angajat");
        ierarhieAngajati.add("AngajatCuDepartament");
        ierarhieAngajati.add("MembruDeProiect");
        ierarhieAngajati.add("ManagerDeProiect");
        ierarhieAngajati.add("DirectorDeCanal");
        ierarhieAngajati.add("DirectorDeDepartament");
        ierarhieAngajati.add("AsistentMembruDeBoard");
        ierarhieAngajati.add("MembruDeBoard");

        for(String x : ierarhieAngajati)
            frecventaAngajati.put(x,0);
        for(Angajat x : Angajati)
        {
            int count = frecventaAngajati.get(x.getTypeAngajat());
            frecventaAngajati.put(x.getTypeAngajat(),count + 1);
        }

        Scanner in = new Scanner(System.in);
        System.out.println("Bine ati venit! Acesta este serviciul pentru ierarhia angajatilor. " +
                           "In cazul in care aveti nevoie de ajutor scrieti \"!help\"");
        while(true)
        {
            System.out.println("Urmatoarea comanda: ");
            String s = in.next();
            s.toLowerCase();

            /*
            *
            *      LA COMANDA EXIT SE SALVEAZA PROGRESUL
            *
            *
             */

            if(s.equals("!exit")){
                try {
                    csvRepo.Logger("exit" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                    List<Angajat> ang = new ArrayList<>();
                    List<DirectorDeCanal> directoriCanal = new ArrayList<>();
                    List<MembruDeProiect> membriiProiect = new ArrayList<>();
                    List<DirectorDeDepartament> directoriDep = new ArrayList<>();
                    for (Angajat angajat : Angajati) {
                        if (angajat.getClass() == Angajat.class) {
                            ang.add(angajat);
                        } else if (angajat.getClass() == DirectorDeCanal.class) {
                            directoriCanal.add((DirectorDeCanal) angajat);
                        } else if (angajat.getClass() == MembruDeProiect.class) {
                            membriiProiect.add((MembruDeProiect) angajat);
                        } else if (angajat.getClass() == DirectorDeDepartament.class) {
                            directoriDep.add((DirectorDeDepartament) angajat);
                        }
                    }
                    csvRepo.write(ang,"./Angajati.csv");
                    csvRepo.write(directoriCanal,"./DirectoriDeCanal.csv");
                    csvRepo.write(membriiProiect,"./MembriDeProiect.csv");
                    csvRepo.write(directoriDep,"./DirectoriDeDepartament.csv");

                } catch (Exception e) {
                    e.printStackTrace();
                }

                System.exit(0);
            } else if (s.equals("!help")) {
                try {
                    csvRepo.Logger("help" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                System.out.println("1. !angajez = comanda pentru a angaja o persoana");
                System.out.println("2. !concediez = comanda pentru a concedia un angajat");
                System.out.println("3. !cresc_salariu = comanda pentru a creste salariul unui angajat");
                System.out.println("4. !scad_salariu = comanda pentru a scadea salariul unui angajat");
                System.out.println("5. !sortare_id = comanda pentru a sorta angajatii in ordinea crescatoare a ID-urilor");
                System.out.println("6. !sortare_nume = comanda pentru a sorta angajatii in ordinea crescatoare a numelor");
                System.out.println("7. !afisare_angajati = comanda pentru a afisa angajatii");
                System.out.println("8. !afisare_ierarhie = comanda pentru a afisa ierarhia angajatilor si cati angajati cu functia respectiva sunt prezenti" +
                                   " unde sus se afla cea mai mica functie");
                System.out.println("9. !numar_angajati = comanda pentru a afisa numarul de angajati");
                System.out.println("10. !acorda_vacanta = comanda pentru a acorda vacanta unui angajat");
            } else if (s.equals("!angajez")){
                try {
                    csvRepo.Logger("angajez" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }

                this.angajez();
                
            } else if (s.equals("!concediez")){

                try {
                    csvRepo.Logger("concediez" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }

                System.out.println("ID-ul persoanei concediate: ");
                int ID_angajat = in.nextInt();
                this.concediez(ID_angajat);

            } else if (s.equals("!cresc_salariu")){
                try {
                    csvRepo.Logger("cresc_salariu" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                this.crescSalariul();

            } else if (s.equals("!scad_salariu")){
                try {
                    csvRepo.Logger("scad_salariu" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                this.scadSalariul();

            } else if (s.equals("!sortare_id")){
                try {
                    csvRepo.Logger("sortare_id" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                Collections.sort(Angajati,new AngajatComparatorById());

            } else if (s.equals("!sortare_nume")){
                try {
                    csvRepo.Logger("sortare_nume" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                Collections.sort(Angajati);

            } else if (s.equals("!afisare_angajati")){
                try {
                    csvRepo.Logger("afisare_angajati" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                for(Angajat x : Angajati){
                    x.afisare();
                    System.out.println();
                }

            } else if (s.equals("!numar_angajati")){
                try {
                    csvRepo.Logger("numar_angajati" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                System.out.print("Numarul total de angajati care au fost in firma: ");
                System.out.println(this.getNumarAngajati());
                System.out.print("Numarul total de angajati actuali: ");
                System.out.println(Angajati.size());

            } else if (s.equals("!acorda_vacanta")){
                try {
                    csvRepo.Logger("acorda_vacanta" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                System.out.println("ID-ul angajatului care va primi vacanta: ");
                int ID_angajat = in.nextInt();
                this.acordaVacanta(ID_angajat);

            } else if(s.equals("!afisare_ierarhie")){
                try {
                    csvRepo.Logger("afisare_ierarhie" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                this.afisareIerarhie();
            } else if (s.length() > 0){
                try {
                    csvRepo.Logger("undefined" + "," + LocalDate.now().toString() + " " + LocalTime.now().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                System.out.println("comanda inexistenta:");
            }
        }
    }

    private void scadSalariul() {
        Scanner in = new Scanner(System.in);
        System.out.println("ID-ul angajatului caruia ii se va scadea salariul: ");
        int ID_angajat = in.nextInt();
        int index = findIndexAngajat(ID_angajat);
        System.out.println("salariul lui este de:" + Angajati.get(index).getSalariu());
        System.out.println("cat doriti sa scadeti din salariu?");
        int aux = in.nextInt();
        if(aux < Angajati.get(index).getSalariu()) {
            Angajati.get(index).setSalariu(Angajati.get(index).getSalariu() - aux);
            System.out.println("Noul salariu este: " + Angajati.get(index).getSalariu());
        }
        else System.out.println("salariul angajatului mai mic decat suma data la tastatura!");
    }

    private void crescSalariul() {
        Scanner in = new Scanner(System.in);
        System.out.println("ID-ul angajatului caruia ii se va creste salariul: ");
        int ID_angajat = in.nextInt();
        int index = findIndexAngajat(ID_angajat);
        System.out.println("salariul lui este de:" + Angajati.get(index).getSalariu());
        System.out.println("cu ce suma doriti sa cresteti salariul?");
        int aux = in.nextInt();
        Angajati.get(index).setSalariu(Angajati.get(index).getSalariu() + aux);
        System.out.println("Noul salariu este: " + Angajati.get(index).getSalariu());
    }

    private void angajez(){
        Scanner in = new Scanner(System.in);
        Angajat noulAngajat;
        String nume;
        String typeAngajat;
        String departament;
        String numeProiect;
        int salariu;

        System.out.println("Ce functie sa aiba?: ");
        typeAngajat = in.next();
        switch (typeAngajat.toLowerCase()){
            case "angajatcudepartament":
                noulAngajat = new AngajatCuDepartament();
                break;
            case "asistentmembrudeboard":
                noulAngajat = new AsistentMembruDeBoard();
                break;
            case "directordecanal":
                noulAngajat = new DirectorDeCanal();
                break;
            case "directordedepartament":
                noulAngajat = new DirectorDeDepartament();
                break;
            case "managerdeproiect":
                noulAngajat = new ManagerDeProiect();
                break;
            case "membrudeboard":
                noulAngajat = new MembruDeBoard();
                break;
            case "membrudeproiect":
                noulAngajat = new MembruDeProiect();
                break;
            default:
                noulAngajat = new Angajat();
                break;
        }
        System.out.println("nume: ");
        nume = in.next();
        noulAngajat.setNume(nume);
        System.out.println("salariu: ");
        salariu = in.nextInt();
        noulAngajat.setSalariu(salariu);
        if(noulAngajat instanceof AngajatCuDepartament) {
            System.out.println("departament: ");
            departament = in.next();
            ((AngajatCuDepartament) noulAngajat).setDepartament(departament);
        }
        if(noulAngajat instanceof MembruDeProiect){
            System.out.println("nume proiect: ");
            numeProiect = in.next();
            ((MembruDeProiect) noulAngajat).setNumeProiect(numeProiect);
        }
        departament = null;
        numeProiect = null;
        int count = frecventaAngajati.get(noulAngajat.getTypeAngajat());
        frecventaAngajati.put(noulAngajat.getTypeAngajat(),count + 1);
        Angajati.add(noulAngajat);
    }

    private int getNumarAngajati(){
        return Angajat.getNrAngajati();
    }

    private int findIndexAngajat(int ID_angajat){
        for(int i=0;i<Angajati.size();i++)
        {
            if(Angajati.get(i).getIdAngajat() == ID_angajat)
                return i;
        }
        return -1;
    }

    private void concediez(int ID_angajat) {
        int index = findIndexAngajat(ID_angajat);
        int count = frecventaAngajati.get(Angajati.get(index).getTypeAngajat());
        if(count > 0)
            frecventaAngajati.put(Angajati.get(index).getTypeAngajat(),count - 1);
        Angajati.remove(index);

    }

    private void afisareIerarhie() {
        for(int i=0;i<ierarhieAngajati.size();i++) {
            int frecventa = frecventaAngajati.get(ierarhieAngajati.get(i));
            if(frecventa != 0)
                System.out.println(ierarhieAngajati.get(i) + ": " + frecventa);
        }
    }

    private void acordaVacanta(int ID_angajat) {
        int index = findIndexAngajat(ID_angajat);
        if(index != -1)
            Angajati.get(index).setVacanta(true);
    }
}
