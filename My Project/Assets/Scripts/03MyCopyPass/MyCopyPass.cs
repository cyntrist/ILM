using Unity.Mathematics;
using UnityEngine.Rendering;
using UnityEngine.Rendering.RenderGraphModule;
using UnityEngine.Rendering.RenderGraphModule.Util;
using UnityEngine.Rendering.Universal;
class MyCopyPass : ScriptableRenderPass
{
    public MyCopyPass()
    {
        requiresIntermediateTexture = true;
    }

    class PassData
    {
        public TextureHandle destination;
    }

    public override void RecordRenderGraph(RenderGraph renderGraph,
    ContextContainer frameData)
    {

        using (var builder = renderGraph.AddRasterRenderPass<PassData>("MyCopyPass", out var passData)) // devuelve un constructor de nodo, con esto se abre y luego hay que cerrarlo
        { 
            // frame data es un contenedor de muchas cosas, con el get coges el objeto que sea de ese tipo (solo habrá uno)
            UniversalResourceData resourceData = frameData.Get<UniversalResourceData>();

            // la textura en la que estábamos escupiendo cosas
            var source = resourceData.activeColorTexture;

            // creamos la textura/target/destino nueva
            // le pedimos al render graph que cree una textura, un recurso que el propio render graph gestionará, será el responsable de su ciclo de vida
            var destinationDesc = renderGraph.GetTextureDesc(source);
            destinationDesc.name = $"MyCopyPas - Pr8-{passName}";
            TextureHandle _destination = renderGraph.CreateTexture(destinationDesc);

            builder.SetRenderAttachment(_destination, 0, AccessFlags.Write);
            builder.SetRenderFunc<PassData>(ExecutePass); // le decimos que funcion queremos que se use para renderizar

            passData.destination = source; // lo que nosotros pongamos aqui terminara en el ExecutePass

            builder.AllowPassCulling(false); // forzamos al render graph para que no elimine la pasada, ya que si no se usa la pasada el render graph la eliminará por eficiencia
        }
    }

    static void ExecutePass(PassData data, RasterGraphContext context)
    {
        //context.cmd.ClearRenderTarget(true, true, data);

        UnityEngine.Vector4 scale_offset = new UnityEngine.Vector4(1.0f, 1.0f, 0.0f, 0.0f);
        Blitter.BlitTexture(context.cmd, data.destination, scale_offset, 0, false);
    }
}