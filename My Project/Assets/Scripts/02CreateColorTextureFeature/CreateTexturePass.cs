using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.RenderGraphModule;
using UnityEngine.Rendering.Universal;

public class CreateTexturePass : ScriptableRenderPass
{
    Color _color;

    public void Setup(Color color)
    {
        _color = color; // me lo pasan desde la render feature
    }

    class PassData
    {
        public Color color;
    }

    public override void RecordRenderGraph(RenderGraph renderGraph, ContextContainer frameData)
    {
        // añadimos un nodo en el grafo y ese nodo va a recibir en su función de renderizado un pass data
        // utilizando esto... haz lo del contexto
        // le pasamos como queremos que se llame la pasada
        using (var builder = renderGraph.AddRasterRenderPass<PassData>("Crear textura de color", out var passData)) // devuelve un constructor de nodo, con esto se abre y luego hay que cerrarlo
        {
            // AQUI NO SE EJECUTA NADA, el orden de muchas de estas cosas dan igual porque aqui solo se apuntan para cuando tengan que ejecutarse

            // frame data es un contenedor de muchas cosas, con el get coges el objeto que sea de ese tipo (solo habrá uno)
            UniversalResourceData resourceData = frameData.Get<UniversalResourceData>();

            // la textura en la que estábamos escupiendo cosas
            var source = resourceData.activeColorTexture;

            // creamos la textura/target/destino nueva
            // le pedimos al render graph que cree una textura, un recurso que el propio render graph gestionará, será el responsable de su ciclo de vida
            var destinationDesc = renderGraph.GetTextureDesc(source);
            destinationDesc.name = $"02ColorPlano-Pr8-{passName}";
            TextureHandle destination = renderGraph.CreateTexture(destinationDesc);

            builder.SetRenderAttachment(destination, 0, AccessFlags.Write);
            builder.SetRenderFunc<PassData>(ExecutePass); // le decimos que funcion queremos que se use para renderizar

            passData.color = _color; // lo que nosotros pongamos aqui terminara en el ExecutePass

            builder.AllowPassCulling(false); // forzamos al render graph para que no elimine la pasada, ya que si no se usa la pasada el render graph la eliminará por eficiencia
        }

    }

    static void ExecutePass(PassData data, RasterGraphContext context)
    {
        context.cmd.ClearRenderTarget(true, true, data.color);
    }
}
