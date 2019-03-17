/*
Objects: 3
Classes: 1
Constructors: 2
Inherited Classes: 0
*/

class Company { //
    /* 


        ameya 
    */ String domainName;

    public Company(){
        this.domainName = "default";
    }

    public Company(String domainName){
        this.domainName = domainName;
    }

    public void getName(){
        System.out.println(this.domainName);
    }

/* 


*/

    public static void main(String[] args) {
        Company defaultObj = new Company();
        Company programizObj = new Company("programiz.com");

        defaultObj.getName();
        programizObj.getName();
    }
}