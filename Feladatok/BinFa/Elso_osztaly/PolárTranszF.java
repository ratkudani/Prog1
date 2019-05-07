public class PolárTranszF {
    
    boolean létezik_tárolt = false;
    double tárolt;
    
    public PolárTranszF() {
        
        létezik_tárolt = false;
        
    }
    
    public double matek_rész() {
        
        if(!létezik_tárolt) {
            
            double u1, u2, v1, v2, w;
            do {
                u1 = Math.random();
                u2 = Math.random();
                
                v1 = 2*u1 - 1;
                v2 = 2*u2 - 1;
                
                w = v1*v1 + v2*v2;
                
            } while(w > 1);
            
            double r = Math.sqrt((-2*Math.log(w))/w);
            
            tárolt = r*v2;
            létezik_tárolt = !létezik_tárolt;
            
            return r*v1;
            
        } else {
            létezik_tárolt = !létezik_tárolt;
            return tárolt;
        }
    }
    
    public static void main(String[] args) {
        
        PolárTranszF g = new PolárTranszF();
        
        for(int i=0; i<2; ++i)
            System.out.println(g.matek_rész());
        
    }
    
}