
package bbj.graphicsobjects;

import bbj.graphicsobjects.*;
import bbj.virtualobjects.*;

import java.awt.*;
import javax.swing.*;

/**
 * Абстрактный класс линии жизни
 * @author Lemon
 */
abstract public class UILifeLine extends SceneItem{
    
    /** Флаг завершенности линии жизни. */
    protected boolean m_isEnded;
    
    /** Координата текста по Х */
    protected int m_textCoordX;
    
    /** Координата текста по У */
    protected int m_textCoordY;

    protected void fillData(int x, int y, String text) {
        this.x = x;
        this.y = 50;
        this.w = 120;
        this.h = 300;
        
        m_text = text;

        setBounds(x, y, w, h);
        this.m_isEdit = false;
        this.m_isSelected = false;
        
    }
    
    
    /**
     * Сделать линию жизни завершенной
     * @param flag Значение флага
     */
    public void setEnded(boolean flag){
        m_isEnded = flag;
    }
    
    /**
     * Узнать завершена ли линия жизни
     * @return Результат
     */
    public boolean isEnded(){
        return m_isEnded;
    }
    
    /**
     * Отрисивка линии жизни
     * @param g Компонент, на котором рисуем
     */
    public void paint(Graphics g){
        specificPaint(g);
                       
        Graphics2D g2 = (Graphics2D)g;
        g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_LCD_HRGB);
        g2.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION, RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
        g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);  

        this.setBounds(this.x,this.y,w+10,h+10);
        
//        g2.setStroke(new BasicStroke(3.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
//                1.0f,new float[]{8.0f,6.0f},0.0f));
//        g2.drawLine(68, 60, 68, 280);           
        
        g2.setStroke(new BasicStroke(1));
       
        if (m_isEnded){
            g.drawLine(x+40, y+260, x+80, y+300);
            g.drawLine(x+40, y+300, x+80, y+260);
        }
                 
        g2.setStroke(new BasicStroke(1.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
                1.0f,new float[]{8.0f,4.0f},0.0f));
        
        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g2.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g2.setColor(Color.black);
                
        g2.drawLine(x+60, y+50, x+60, y+280);
        
         // Разбиваем текст на массив символов
        char [] drawedText = m_text.toCharArray();
        char [] dots = {'.','.','.'};
        
        g.drawChars(drawedText, 0, java.lang.Math.min(13, m_text.length()), m_textCoordX, m_textCoordY);
        
        if (m_text.length() >= 14)
            g.drawChars(dots, 0, 3, m_textCoordX+90, m_textCoordY);

        if (m_isEdit) 
            f.repaint();
    }
    
    abstract public void specificPaint(Graphics g);
}
